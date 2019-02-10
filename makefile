CC = g++-7
CFLAGS = -Wall -std=c++1z -g
EXEC_NAME = bin/LeoinTillValhalar
OBJECTS = bin/objects/
DIR = bin bin/objects
OBJ_FILES =  $(OBJECTS)main.o $(OBJECTS)punchRabbit.o $(OBJECTS)Fond.o $(OBJECTS)button.o $(OBJECTS)joe.o $(OBJECTS)fireBird.o $(OBJECTS)environement.o $(OBJECTS)coordTab.o $(OBJECTS)adversaire.o $(OBJECTS)blocus_plateForme.o $(OBJECTS)decor_list.o $(OBJECTS)blocusAdv.o $(OBJECTS)fonction.o $(OBJECTS)BlackBird.o $(OBJECTS)jeu.o $(OBJECTS)pixelCoordTab.o $(OBJECTS)decor.o $(OBJECTS)score.o $(OBJECTS)hitbox.o $(OBJECTS)checkpoint.o $(OBJECTS)blackScreen.o $(OBJECTS)piece.o $(OBJECTS)perso.o $(OBJECTS)niveau.o $(OBJECTS)plateforme.o $(OBJECTS)fin_niveau.o $(OBJECTS)generalTexture.o $(OBJECTS)panda.o $(OBJECTS)laser.o $(OBJECTS)Vue.o

all : $(EXEC_NAME)

clean :
	rm $(EXEC_NAME) $(OBJ_FILES)


$(EXEC_NAME) : $(DIR) $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) -lsfml-graphics -lsfml-window -lsfml-system

$(OBJECTS)%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< -lsfml-graphics -lsfml-window -lsfml-system

$(DIR) :
	mkdir bin
	mkdir bin/objects