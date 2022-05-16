#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

int main() {
	const int height = 17;
	const int width = 240;
	RenderWindow window(VideoMode(width*5, height*32), "MARIO by Zyryanov", Style::Close);
	String map[height] = {
"sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss",
"s                                                                                                                                                                                                                                             s",
"s                                                                                                                                                                                                                                             s",
"s                                                                                                                                                                                                                                             s",
"s                                                                                                                                                                                                                                             s",
"s                                                                                       xxxxxxxxx   xxxx                              xxx    xxxx                                                                                             s",
"s                      u                                                                bbbbbbbbb   bbbq                  u           bbb    bqqb                                                        x                                    s",
"s                                                                                                                                                                                                       xr                                    s",
"s                                                                                                                                                                                                      xrr                                    s",
"s                                                                                   xxx                x      xx                    x         xx                                    xxxx              xrrr                                    s",
"s               u    bqbqb                                                          bqb                b      bb       u  u  u      b         bb     r  r          rr  r            bbqb             xrrrr                                    s",
"s                                                                                                                                                   rr  rr        rrr  rr                           xrrrrr                                    s",
"s                                                                                                                                                  rrr  rrr      rrrr  rrr                         xrrrrrr                                    s",
"s                                        xxxxxxx                                                                                                  rrrr  rrrr    rrrrr  rrrr                        rrrrrrr                                    s",
"eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee  eeeeeeeeeeeeeeeee  eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee  eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee",
"eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee  eeeeeeeeeeeeeeeee  eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee  eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee",
"eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee  eeeeeeeeeeeeeeeee  eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee  eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee",
	};
	Texture mapTexture;
	mapTexture.loadFromFile("C:/Users/Zyryanov/Desktop/УРТК/C++ and C#/11 Mario/map.png");
	Sprite mapSprite(mapTexture);
	Music music;
	music.openFromFile("C:/Users/Zyryanov/Desktop/УРТК/C++ and C#/11 Mario/8bit.ogg");
	music.play();
	Image icon;
	icon.loadFromFile("C:/Users/Zyryanov/Desktop/УРТК/C++ and C#/11 Mario/icon.png");
	window.setIcon(840, 859, icon.getPixelsPtr());
	Image heroImage;
	heroImage.loadFromFile("C:/Users/Zyryanov/Desktop/УРТК/C++ and C#/11 Mario/hero.png");
	heroImage.createMaskFromColor(Color(255, 255, 255));
	Texture heroTexture;
	heroTexture.loadFromImage(heroImage);
	Sprite heroSprite (heroTexture);
	heroSprite.setTextureRect(IntRect(0, 0, 64, 85));
	heroSprite.setPosition(0, 360);
	float nowFrame = 0; //хранит текущий кадр для анимации
	Clock clock;
	while (window.isOpen()) {
		float time = clock.getElapsedTime().asMicroseconds(); 
		clock.restart(); 
		time = time / 800; //чем выше делитель, тем выше плавность (аналог FPS)
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			heroSprite.setScale(1, 1);
			nowFrame += 0.005 * time; //служит для прохождения по кадрам. переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (nowFrame > 4) 
				nowFrame -= 4; //проходимся по кадрам с первого по пятый включительно. если пришли к пятому кадру - откидываемся назад
			heroSprite.setTextureRect(IntRect(80 * int(nowFrame), 0, 75, 85)); //проходимся по координатам Х. 
			heroSprite.move(0.1*time, 0); 
			/*heroSprite.setTextureRect(IntRect(80, 5, 70, 80));
			heroSprite.setTextureRect(IntRect(171, 0, 59, 85));
			heroSprite.setTextureRect(IntRect(246, 0, 80, 85));
			heroSprite.setTextureRect(IntRect(337, 0, 70, 85));*/
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			heroSprite.setScale(-1, 1); //отразим по горизонтали
			nowFrame += 0.005 * time; 
			if (nowFrame > 4)
				nowFrame -= 4; 
			heroSprite.setTextureRect(IntRect(80 * int(nowFrame), 0, 75, 85)); 
			heroSprite.move(-0.1 * time, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) { 
			heroSprite.move(0, -0.1*time); 
			heroSprite.setTextureRect(IntRect(418, 0, 85, 85)); 
		} 
		//else
			//heroSprite.setTextureRect(IntRect(0, 0, 64, 85));
		window.clear();
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++) {
				if (map[i][j] == ' ' || map[i][j] == 's')
					mapSprite.setTextureRect(IntRect(128, 0, 32, 32));
				if (map[i][j] == 'e')  
					mapSprite.setTextureRect(IntRect(0, 0, 32, 32));
				if (map[i][j] == 'u')
					mapSprite.setTextureRect(IntRect(32, 0, 32, 32));
				if (map[i][j] == 'b')
					mapSprite.setTextureRect(IntRect(64, 0, 32, 32));
				if (map[i][j] == 'q')
					mapSprite.setTextureRect(IntRect(96, 0, 32, 32));
				mapSprite.setPosition(j * 32, i * 32);
				window.draw(mapSprite);
			}
		window.draw(heroSprite);
		window.display();
	}
}
