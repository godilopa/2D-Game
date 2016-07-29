
#include "../include/IOArchivo.h"
#include <string.h>
#include <stdlib.h>

IOArchivo::File IOArchivo::OpenFile(File& file, const char* fileName, const char* mode){

	fopen_s(&file, fileName, mode); //pasamos por referencia file para que se modifique dentro de fopen_s

	if (file){
		return file;
	}
	else{
		printf("Error al abrir el archivo");
		return nullptr;
	}
}

int IOArchivo::CloseFile(File file){
	return fclose(file);
}

unsigned int IOArchivo::ReadFile(File file, char* buffer, unsigned int n){

	return fread_s(buffer, n, sizeof(char), n, file); //leemos de un buffer n elementos de tamaño sizeof(char) devuelve los que see han leido
}

unsigned int IOArchivo::WriteFile(File file, const char* buffer, unsigned int n){ //guardamos en un buffer n elementos de tamaño sizeof(char)	
	//devuelve los caracteres escritos
	return fwrite(buffer, sizeof(char), n, file);
}