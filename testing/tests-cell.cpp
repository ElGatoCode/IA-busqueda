#include "../include/Cell.hpp"
#include "catch.hpp"

#include <sstream>
#include <string>

using namespace std;

TEST_CASE("Pruebas de celda", "[cell]") {
	
	Cell myCell(3,2);
	
	//Inicializa y accede bien a row_ y column
	REQUIRE(myCell.get_row() == 3);
	REQUIRE(myCell.get_column() == 2);
	
  //set_pos
  myCell.set_pos(6,7);
  REQUIRE(myCell.get_row() == 6);
  REQUIRE(myCell.get_column() == 7);

	//is_free()
	REQUIRE(myCell.is_free() == true);
	
	stringstream buff;
	buff << myCell;

	//Imprime ' ' cuando free
	REQUIRE(buff.str() == string(" "));

	//Setea el estado  a obstáculo
	myCell.set_state(obstacle_c);
	REQUIRE(!myCell.is_free());

  //Setea el estado a pisada
  myCell.set_state(stepped_c);
  REQUIRE(myCell.is_stepped());

	//Imprime 'X' cuando stepped
	buff.str("");
	buff << myCell;
	REQUIRE(buff.str() == string("X"));
}


TEST_CASE("print", "[cell] [print]") {
  Cell myCell;
  stringstream buff;

  buff << myCell;
  REQUIRE(buff.str() == string(" "));

  buff.str("");
  myCell.set_state(stepped_c);
  buff << myCell;
  REQUIRE(buff.str() == string("X"));

  buff.str("");
  myCell.set_state(obstacle_c);
  buff << myCell;
  REQUIRE(buff.str() == string("#"));
}