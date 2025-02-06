#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "ball_object_collisions.h"

SpriteRenderer* Renderer;
GameObject* Player;
BallObject* Ball;

Game::Game(unsigned int widht, unsigned int height) : State(GAME_ACTIVE), Keys(), Width(widht), Height(height)
{
}

Game::~Game()
{
	delete Renderer;
	delete Player;
	delete Ball;
}

void Game::Init()
{
	ResourceManager::LoadShader("./src/7.-EnPractica/7.3.-Game/sprite.vert", "./src/7.-EnPractica/7.3.-Game/sprite.frag", nullptr, "sprite");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("imge", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	Shader shader = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(shader);

	ResourceManager::LoadTexture("./texturas/awesomeface.png", true, "face");

	//Codiggo Añadido
	ResourceManager::LoadTexture("./texturas/background.jpg", false, "background");
	ResourceManager::LoadTexture("./texturas/block.png", false, "block");
	ResourceManager::LoadTexture("./texturas/block_solid.png", false, "block_solid");
	ResourceManager::LoadTexture("./texturas/paddle.png", true, "paddle");

	GameLevel one; one.Load("./src/7.-EnPractica/7.3.-Game/levels/one.lvl", this->Width, this->Height / 2);
	GameLevel two; two.Load("./src/7.-EnPractica/7.3.-Game/levels/two.lvl", this->Width, this->Height / 2);
	GameLevel three; three.Load("./src/7.-EnPractica/7.3.-Game/levels/three.lvl", this->Width, this->Height / 2);
	GameLevel four; four.Load("./src/7.-EnPractica/7.3.-Game/levels/four.lvl", this->Width, this->Height / 2);
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->Level = 0;

	glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
	Ball = new BallObject(ballPos, BALL_RADIUS, INITAL_BALL_VELOCITY, ResourceManager::GetTexture("face"));
}

void Game::ProcessInput(float dt)
{
	
	if (this->State == GAME_ACTIVE) {
		float velocity = PLAYER_VELOCITY * dt;

		if (this->Keys[GLFW_KEY_A]) {
			if (Player->Position.x >= 0.0f) {
				Player->Position.x -= velocity;
				if (Ball->Stuck) {
					Ball->Position.x -= velocity;
				}
			}
		}

		if (this->Keys[GLFW_KEY_D]) {
			if (Player->Position.x <= this->Width - Player->Size.x) {
				Player->Position.x += velocity;
				if (Ball->Stuck) {
					Ball->Position.x += velocity;
				}
			}
		}

		if (this->Keys[GLFW_KEY_SPACE]) {
			Ball->Stuck = false;
		}
	}

}

void Game::Update(float dt)
{
	Ball->Move(dt, this->Width);
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE) {
		Texture2D image = ResourceManager::GetTexture("background");
		Renderer->DrawSprite(image, glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);

		this->Levels[this->Level].Draw(*Renderer);

		Player->Draw(*Renderer);

		Ball->Draw(*Renderer);
	}
	
	//Renderer->DrawSprite(image, glm::vec2(200.0f, 200.0f), glm::vec2 (300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
