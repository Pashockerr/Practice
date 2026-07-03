run_desktop:
	g++ ./src/main.cpp ./src/Scene.cpp ./src/Sprite.cpp ./src/Terminal.cpp ./src/Banknote.cpp ./src/Reciever.cpp ./src/Button.cpp ./src/mouse_handler.cpp ./lib/libraylib.a -lX11 -o a.out
	./a.out
