#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

class Player
{
public:
	Player(glm::vec3 position = glm::vec3(1.0f,0.0f,0.0f));
	~Player();
	glm::mat4 getModel(float deltaTime);
	void yawRight(float deltaTime);
	void yawLeft(float deltaTime);
	void pitchUP(float deltaTime);
	void pitchDown(float deltaTime);
	void accelerate(float deltaTime);
	void reverse(float deltaTime);
	glm::vec3 getPosition();
private:
	float yaw = 90.0f; // degrees
	float pitch = 0.0f; // degrees
	float roll = 0.0f; // degrees
	float rotationAngle = 0.03; 
	float velocity = 0.05f;
	glm::quat yawQuat = glm::quat(0.0f, 0.0f, 1.0f, 0.0f);
	glm::quat pitchQuat = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
	glm::quat rollQuat = glm::quat(0.0f, 1.0f, 0.0f, 0.0f);

	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 position;
};

