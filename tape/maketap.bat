@echo off
..\utils\pasmo loader.asm loader.bin
..\utils\GenTape ninjajar.tap					^
	basic 'Ninjajar' 10	loader.bin		^
	data				loading.bin		^
	data				ram1.bin		^
	data				ram3.bin		^
	data				ram4.bin		^
	data				ram6.bin		^
	data				ram7.bin		^
	data				ninjajar.bin
