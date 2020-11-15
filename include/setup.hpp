/**
 * Este fichero se utiliza para definir los 'estilos' para imprimir texto
 */
#pragma once

#include "termcolor/termcolor.hpp"
#include "iostream"

using namespace std; 

// Colors setup
const auto bold_cyan = [](ostream& os) -> ostream& {
  os << termcolor::bold << termcolor::cyan;
  return os;
};

const auto bold_weak_red = [](ostream& os) -> ostream& {
  os << termcolor::bold << termcolor::color<255,104,125>;
  return os;
};

const auto bold_mostard = [](ostream& os) -> ostream& {
  os << termcolor::bold << termcolor::color<176,163,210>;
  return os;
};

const auto sub_title_color = bold_mostard;
const auto error_color = bold_weak_red;
const auto input_names_color = termcolor::color<242,216,164>;
const auto reset = termcolor::reset;