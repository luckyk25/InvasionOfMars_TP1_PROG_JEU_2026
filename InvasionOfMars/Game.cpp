#include "Game.h"
#include "ContentPipeline.h"
#include <iostream>
Game::Game()
{
	renderWindow.create(VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }, 32), "Invasion of Mars");// , Style::None, State::Fullscreen);
	
	
	mainView = View(FloatRect({ 0.0f, 0.0f }, { SCREEN_WIDTH, SCREEN_HEIGHT }));
	mainView.setCenter({ WORLD_WIDTH / 2.0f , WORLD_HEIGHT / 2.0f });

	hudView = View(FloatRect({ 0.0f, 0.0f }, { SCREEN_WIDTH, SCREEN_HEIGHT }));

	//Synchonisation coordonnée à l'écran!  Normalement 60 frames par secondes. À faire absolument
	//renderWindow.setVerticalSyncEnabled(true);  //De plus en plus d'écrans sont rafraichis à plus de 60 frames par seconde, alors attention.
	renderWindow.setFramerateLimit(60);  //Équivalent... normalement, mais pas toujours. À utiliser si la synchonisation de l'écran fonctionne mal.
	//https://www.sfml-dev.org/tutorials/3.0/window/window/#controlling-the-framerate

	renderWindow.setKeyRepeatEnabled(false);
	srand((int)time(0));  //Pour générer le seed random
}

int Game::run()
{
	if (!init())return EXIT_FAILURE;

	while (renderWindow.isOpen())
	{
		calculateDeltaTime();
		getInputs();
		update();
		draw();
	}

	if (!unload())return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

bool Game::init()
{
	if (!ContentPipeline::getInstance().loadContent()) return false;
	if (!music.openFromFile(std::filesystem::path("Ressources\\Sounds\\Music\\Carpenter_brut_remorse.ogg"))) return false;

	field = new Sprite(ContentPipeline::getInstance().getBackgroundTexture());
	field->setPosition({ 0.0f, 0.0f });
	field->setColor(Color(193, 68, 14, 255)); //Couleur "Rouge sol de Mars"
	player.setCollisionCircleRadius(32);

	player.init();
	player.setPosition(WORLD_CENTER_X, WORLD_CENTER_Y);

	for (int i = 0; i < DEFAULT_ALIEN_COUNT; i++)
		aliens[i].init(rand() % 3);


	for (int i = 0; i < NBR_BULLETS; i++)
	{
		bullets[i].setTexture(ContentPipeline::getInstance().getProjectileTexture(1));
		bullets[i].setBulletSound(ContentPipeline::getInstance().getShotBuffer());
	}

	for (int i = 0; i < NBR_BONUS_TYPE; i++)
		for (int j = 0; j < NBR_OF_BONUS; j++)
			bonuses[i][j].init(i);

	hud.hudInit();

	player.activate();
	music.setLooping(true);
	//music.play();
	return true;


}

void Game::getInputs()
{
	inputs.reset();
	//On passe l'événement en référence et celui-ci est chargé du dernier événement reçu!
	while (const optional event = renderWindow.pollEvent())
	{
		//x sur la fenêtre
		if (event->is<Event::Closed>())	renderWindow.close();
		if (const Event::KeyPressed* keyPressed = event->getIf<Event::KeyPressed>())
		{
			if (keyPressed->scancode == Keyboard::Scan::P) inputs.pause = true;
		}
	}

	if (gameOver) return;
	if (Joystick::isConnected(0))
	{
		//le / 100 à la fin: on ramène le tout à une échelle de 0 à 1: plus simple
		inputs.moveHorizontal = inputs.manageGamepadAxis(Joystick::getAxisPosition(0, Joystick::Axis::X));
		inputs.moveVertical = inputs.manageGamepadAxis(Joystick::getAxisPosition(0, Joystick::Axis::Y));
		inputs.isGamepadActive = true;
	}
	else
	{
		if (Keyboard::isKeyPressed(Keyboard::Scan::A)) inputs.moveHorizontal -= 1.0f;
		if (Keyboard::isKeyPressed(Keyboard::Scan::D)) inputs.moveHorizontal += 1.0f;
		if (Keyboard::isKeyPressed(Keyboard::Scan::W)) inputs.moveVertical -= 1.0f;
		if (Keyboard::isKeyPressed(Keyboard::Scan::S)) inputs.moveVertical += 1.0f;

		inputs.fire = Mouse::isButtonPressed(Mouse::Button::Left);
		inputs.adjustInputs();

		inputs.mousePosition = renderWindow.mapPixelToCoords(Mouse::getPosition(renderWindow));
	}
}

//Vous devrez centrer la vue sur le player: https://www.sfml-dev.org/tutorials/2.6/graphics-view-fr.php
void Game::update()
{
	manageGameConditions();
	if (isInPause || gameOver) return;
	if (hud.isPlayerDead()) gameOver = true;
	//On peut déplacer la vue, mais on peut aussi lui la centrer sur une position précise, 
	//comme celle du joueur (avec la méthode setCenter).  Quand votre joueur va se déplacer 
	//vous devrez centrer la vue sur lui.
	if (recoil > 0) recoil--;
	if (inputs.fire && player.isActive()) fire();

	for (int i = 0; i < NBR_BULLETS; i++)
		bullets[i].fly();
	
	Alien::setDestination(player.getPosition());
	
	for (int i = 0; i < DEFAULT_ALIEN_COUNT; i++)
		aliens[i].update();

	manageAlienSpawn();
	checkBulletAlienCollision();
	hud.update();
	if(!player.isActive())
		managePlayerRespawn();
	if (playerInvincible)
	{
		//Todo à mettre dans le player.
		if (--playerInvincibleTimer <= 0) 
		{
			playerInvincible = false;
			player.switchTransparence(playerInvincible);
		}
	}
	checkPlayerAlienCollision();
	managePlayerMovment();
	ajustCrossingWorldLimits();
}

void Game::manageAlienSpawn() 
{
	if (alienSpawnTimer > 0) {
		alienSpawnTimer--;
	}
	else {
		for (int i = 0; i < DEFAULT_ALIEN_COUNT; i++) {
			if (!aliens[i].isActive()) {
				aliens[i].spawnAlien();
				break;
			}
		}
		alienSpawnTimer = ALIEN_SPAWN_SPEED;
	}
}

void Game::manageGameConditions()
{
	if (inputs.pause)
	{
		isInPause = !isInPause;

		if (isInPause || gameOver) 
		{
			music.pause();
			if(!gameOver)
				hud.displayPause(true);
		}
		else 
		{
			music.play();
			hud.displayPause(false);
		}
	}
}

void Game::checkPlayerAlienCollision() 
{
	if (!player.isActive()) return;
	for(int i = 0; i < DEFAULT_ALIEN_COUNT; i++)
	{
		if (aliens[i].isActive() && player.isCircleColliding(aliens[i])) 
		{
			if(!playerInvincible)
			{				
				Alien::changeDirection();
				player.deactivate();
				hud.decreaseNumberOfLives();
				playerRespawnTimer = PLAYER_RESPAWN_TIME;
				break;
			}
		}
	}
}

void Game::managePlayerRespawn() 
{
	if (playerRespawnTimer > 0)
	{
		playerRespawnTimer--;
		if (playerRespawnTimer <= 0)
		{
			player.activate();
			playerInvincibleTimer = INVINCIBLE_TIMER;
			playerInvincible = true;
			player.switchTransparence(playerInvincible);
			Alien::changeDirection();
		}
	}
}

void Game::checkBulletAlienCollision() 
{
	for(int i = 0; i < NBR_BULLETS; i++) 
	{
		for(int j = 0; j < DEFAULT_ALIEN_COUNT; j++) 
		{
			if(bullets[i].isActive() && aliens[j].isActive() && bullets[i].isCircleColliding(aliens[j]))
			{
				int randomNumber = (rand() % BONUS_SPAWN_RATE) + 0;
				switch(randomNumber)
				{
					case NUKE_NUMBER:
						for (int i = 0; i < NBR_OF_BONUS; i++)
						{
							if (!bonuses[NUKE_NUMBER][i].isActive())
							{
								bonuses[NUKE_NUMBER][i].spawnBonus(aliens[j].getPosition());
								break;
							}
						}
						break;
					case FAST_NUMBER:
						for (int i = 0; i < NBR_OF_BONUS; i++)
						{
							if (!bonuses[FAST_NUMBER][i].isActive())
							{
								bonuses[FAST_NUMBER][i].spawnBonus(aliens[j].getPosition());
								break;
							}
						}
						break;
				}
				bullets[i].deactivate();
				aliens[j].deactivate();
				hud.incrementScore();
			}
		}
	}
}


void Game::managePlayerMovment() 
{
	player.move(inputs.moveHorizontal * PLAYER_SPEED, inputs.moveVertical * PLAYER_SPEED);
	player.setPlayerDirection(inputs.mousePosition);
	player.keepPlayerInBound();
}

void Game::draw()
{
	//Toujours important d'effacer l'écran précédent
	renderWindow.clear();
	renderWindow.setView(mainView);
	renderWindow.draw(*field);

	player.draw(renderWindow);
	for (int i = 0; i < DEFAULT_ALIEN_COUNT; i++) 
		aliens[i].draw(renderWindow);

	for (int i = 0; i < NBR_BULLETS; i++)
		bullets[i].draw(renderWindow);
	
	for (int i = 0; i < NBR_BONUS_TYPE; i++)
		for (int j = 0; j < NBR_OF_BONUS; j++)
			bonuses[i][j].draw(renderWindow);

	renderWindow.setView(hudView);
	hud.draw(renderWindow);
	renderWindow.setView(mainView);
	renderWindow.display();
}

bool Game::unload()
{
	if (field != nullptr) delete field;
	return true;
}

void Game::calculateDeltaTime()
{
	deltaTime = clock.restart().asSeconds();
}

void Game::fire()
{
	//Recoil doit être à 0 pour avoir le droit de tirer concrètement
	if (recoil > 0) return;

	for (int i = 0; i < NBR_BULLETS; i++)
	{
		if (!bullets[i].isActive())
		{
			bullets[i].fire(player, player.getVectorialPush());
			recoil = MAX_RECOIL;
			break;
		}
	}
}

void Game::ajustCrossingWorldLimits()
{
	Vector2f playerPosition = player.getPosition();

	if (playerPosition.x < WORLD_LIMIT_MIN_X) playerPosition.x = WORLD_LIMIT_MIN_X;
	else if (playerPosition.x > WORLD_LIMIT_MAX_X) playerPosition.x = WORLD_LIMIT_MAX_X;

	if (playerPosition.y < WORLD_LIMIT_MIN_Y) playerPosition.y = WORLD_LIMIT_MIN_Y;
	else if (playerPosition.y > WORLD_LIMIT_MAX_Y) playerPosition.y = WORLD_LIMIT_MAX_Y;

	mainView.setCenter(playerPosition);
}