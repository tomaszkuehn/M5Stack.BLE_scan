// ----------------------------------------------------------------------------
// Copyright (C) 2020, Tomasz Kuehn
//
// These coded instructions, statements, and computer programs are free
// for personal use.
//
// Maintainer: Tomasz Kuehn
//
// Description: Neopixels M5Stack Fire interface
// ----------------------------------------------------------------------------

#pragma once

#include <Adafruit_NeoPixel.h>

#define M5STACK_FIRE_NEO_NUM_LEDS  10
#define M5STACK_FIRE_NEO_DATA_PIN  15

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(M5STACK_FIRE_NEO_NUM_LEDS, M5STACK_FIRE_NEO_DATA_PIN,
                           NEO_GRB + NEO_KHZ800);
