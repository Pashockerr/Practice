run_desktop:
	g++ ./src/main.cpp ./src/Scene.cpp ./src/Sprite.cpp ./src/Banknote.cpp ./src/Reciever.cpp ./src/mouse_handler.cpp ./lib/libraylib.a -lX11
	./a.out
