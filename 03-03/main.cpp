#include "Vehicle.h"
#include "Car.h"
#include "Bicycle.h"

#include <memory>

int main() {

	std::unique_ptr<Vehicle> vehicle1 = std::make_unique<Car>();
	std::unique_ptr<Vehicle> vehicle2 = std::make_unique<Bicycle>();

	vehicle1->Move();  // 車の移動
	vehicle2->Move();  // 自転車の移動

	return 0;
}