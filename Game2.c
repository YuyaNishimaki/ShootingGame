typedef volatile unsigned short hword;

#define VRAM1 0x0001//1
#define VRAM2 0x00F0//240
#define BACKC 0x0000//背景色（黒色）
#define PLACL 0x7FFF//プレイヤー色（白色）
#define ENECL 0x7FE0//敵色（siann）

void draw_point (hword, hword, hword);//点表示
void draw_circle (hword, hword, hword, hword);//円を描く
void draw_rect (hword, hword, hword, hword, hword);//四角を描く
void draw_player (hword, hword, hword, int[11][11]);//プレイヤーを描く
void draw_enemy (hword, hword, hword, int[11][11]);//敵を描く
void delete (hword, hword);//爆発して消す
hword crash (hword, hword);//衝突判定
hword countUp1 (hword);//弾のカウント
hword countUp2 (hword);
hword countUp3 (hword);
int main2 (void);//中級
int main3 (void);//上級
int main4 (void);

int main (void){
	hword *ptr;
	hword xp;//Playerのx座標
	hword yp;//Playerのy座標
	hword xpv;//Playerのxの速さ
	hword xe;//Enemyのx座標
	hword ye;//Enemyのy座標
	hword xev;//Enemyのxの速さ
	hword pshot[5][2];//プレイヤーの弾[x座標、y座標]
	hword eshot[5][2];//敵の弾[x座標、y座標]
	hword shot_v;//弾の速さ
	hword pshotNow;//next
	hword eshotNow;//next
	hword color1;//BACKC
	hword color2;//PLACL
	hword color3;//ENECL
	hword random;//敵の行動を決めるランダムな値
	hword a;
	hword b;
	hword c;
	hword end;
	hword i;
	hword j;
	int playerShape[11][11];
	int enemyShape[11][11];

	//モード3に変更
	ptr = (hword*)0x04000000;
	*ptr = 0xF03;
	
	//初期化
	xp = 120;
	yp = 145;
	xpv = 5;
	xe = 120;
	ye = 15;
	xev = 5;
	shot_v = 5;
	for(i = 0; i < 5; i++){
		pshot[i][0] = 0;
		pshot[i][1] = 0;
		eshot[i][0] = 0;
		eshot[i][1] = 0;		
	}
	pshotNow = 0;
	eshotNow = 0;
	random = 0;
	a = 0;
	b = 0;
	c = 0;
	color1 = BACKC;
	color2 = PLACL;
	color3 = ENECL;
	end = 0;

	for(i = 0; i < 11; i++){
		for(j = 0; j < 11; j++){
			playerShape[i][j] = 0;
		}
	}
	playerShape[1][6] = 1;
	playerShape[1][7] = 1;
	playerShape[1][8] = 1;
	playerShape[1][9] = 1;
	playerShape[2][4] = 1;
	playerShape[2][5] = 1;
	playerShape[2][6] = 1;
	playerShape[2][7] = 1;
	playerShape[2][8] = 1;
	playerShape[2][9] = 1;
	playerShape[2][10] = 1;
	playerShape[3][7] = 1;
	playerShape[3][8] = 1;
	playerShape[4][3] = 1;
	playerShape[4][4] = 1;
	playerShape[4][5] = 1;
	playerShape[4][6] = 1;
	playerShape[4][7] = 1;
	playerShape[4][8] = 1;
	playerShape[4][9] = 1;
	playerShape[4][10] = 1;
	playerShape[5][1] = 1;
	playerShape[5][2] = 1;
	playerShape[5][3] = 1;
	playerShape[5][7] = 1;
	playerShape[5][8] = 1;
	playerShape[5][9] = 1;
	playerShape[5][10] = 1;
	playerShape[9][6] = 1;
	playerShape[9][7] = 1;
	playerShape[9][8] = 1;
	playerShape[9][9] = 1;
	playerShape[8][4] = 1;
	playerShape[8][5] = 1;
	playerShape[8][6] = 1;
	playerShape[8][7] = 1;
	playerShape[8][8] = 1;
	playerShape[8][9] = 1;
	playerShape[8][10] = 1;
	playerShape[7][7] = 1;
	playerShape[7][8] = 1;
	playerShape[6][3] = 1;
	playerShape[6][4] = 1;
	playerShape[6][5] = 1;
	playerShape[6][6] = 1;
	playerShape[6][7] = 1;
	playerShape[6][8] = 1;
	playerShape[6][9] = 1;
	playerShape[6][10] = 1;

	for(i = 0; i < 11; i++){
		for(j = 0; j < 11; j++){
			enemyShape[i][j] = 0;
		}
	}
	enemyShape[0][5] = 1;
	enemyShape[0][6] = 1;
	enemyShape[0][7] = 1;
	enemyShape[0][8] = 1;
	enemyShape[1][4] = 1;
	enemyShape[1][5] = 1;
	enemyShape[2][1] = 1;
	enemyShape[2][3] = 1;
	enemyShape[2][4] = 1;
	enemyShape[2][5] = 1;
	enemyShape[2][6] = 1;
	enemyShape[2][7] = 1;
	enemyShape[2][8] = 1;
	enemyShape[3][2] = 1;
	enemyShape[3][3] = 1;
	enemyShape[3][5] = 1;
	enemyShape[3][6] = 1;
	enemyShape[3][7] = 1;
	enemyShape[3][9] = 1;
	enemyShape[4][3] = 1;
	enemyShape[4][4] = 1;
	enemyShape[4][5] = 1;
	enemyShape[4][6] = 1;
	enemyShape[4][7] = 1;
	enemyShape[4][9] = 1;
	enemyShape[5][3] = 1;
	enemyShape[5][4] = 1;
	enemyShape[5][5] = 1;
	enemyShape[5][6] = 1;
	enemyShape[5][7] = 1;
	enemyShape[10][5] = 1;
	enemyShape[10][6] = 1;
	enemyShape[10][7] = 1;
	enemyShape[10][8] = 1;
	enemyShape[9][4] = 1;
	enemyShape[9][5] = 1;
	enemyShape[8][1] = 1;
	enemyShape[8][3] = 1;
	enemyShape[8][4] = 1;
	enemyShape[8][5] = 1;
	enemyShape[8][6] = 1;
	enemyShape[8][7] = 1;
	enemyShape[8][8] = 1;
	enemyShape[7][2] = 1;
	enemyShape[7][3] = 1;
	enemyShape[7][5] = 1;
	enemyShape[7][6] = 1;
	enemyShape[7][7] = 1;
	enemyShape[7][9] = 1;
	enemyShape[6][3] = 1;
	enemyShape[6][4] = 1;
	enemyShape[6][5] = 1;
	enemyShape[6][6] = 1;
	enemyShape[6][7] = 1;
	enemyShape[6][9] = 1;


	//背景の塗りつぶし
	ptr = (hword*)0x06000000;
	for(i = 0; i < 38400; i++){
		*ptr = color1;
		ptr += VRAM1;
	}
	draw_player (xp, yp, color2, playerShape);
	while(1){
		random += 7 + a + b + c;
		//ボタン操作
		ptr = (hword*)0x04000130;
		if((*ptr & 0x0010) != 0x0010){//右
			if(xp <= 230){
				draw_player (xp, yp, color1, playerShape);
				xp = xp + xpv;
				draw_player (xp, yp, color2, playerShape);
				a++;
			}
		}else if((*ptr & 0x0020)!=0x0020){//左
			if(xp >= 7){
				draw_player (xp, yp, color1, playerShape);
				xp = xp - xpv;
				draw_player (xp, yp, color2, playerShape);
				b += 2;
			}
		}

		if((*ptr & 0x0001) != 0x0001){//A
			if(pshot[pshotNow][0] == 0){
				pshot[pshotNow][0] = xp;
				pshot[pshotNow][1] = yp - 10;
				pshotNow = countUp1 (pshotNow);
				c += 5;
			}
		}

		//敵の動き
		if((random % 3) == 1){
			if(xe <= 229){
				draw_enemy (xe, ye, color1, enemyShape);
				xe = xe + xev;
				draw_enemy (xe, ye, color3, enemyShape);
			}
		}else if((random % 3) == 2){
			if(xe >= 7){
				draw_enemy (xe, ye, color1, enemyShape);
				xe = xe - xev;
				draw_enemy (xe, ye, color3, enemyShape);
			}
		}else if((random % 3) == 0){
			if(eshot[eshotNow][0] == 0){
				eshot[eshotNow][0] = xe;
				eshot[eshotNow][1] = ye + 10;
				eshotNow = countUp1 (eshotNow);
			}
		}		
		
		//弾を動かす
		for(i = 0; i < 5; i++){
			if((pshot[i][0] != 0) && (pshot[i][1] != 0)){
				draw_circle (pshot[i][0], pshot[i][1], 3, color1);
				pshot[i][1] = pshot[i][1] - shot_v;
				if(pshot[i][1] <= 3){
					pshot[i][0] = 0;
					pshot[i][1] = 0;
				}else{
					draw_circle (pshot[i][0], pshot[i][1], 3, color2);
				}
			}
		}

		for(i = 0; i < 5; i++){
			if((eshot[i][0] != 0) && (eshot[i][1] != 0)){
				draw_circle (eshot[i][0], eshot[i][1], 3, color1);
				eshot[i][1] = eshot[i][1] + shot_v;
				if(eshot[i][1] >= 157){
					eshot[i][0] = 0;
					eshot[i][1] = 0;
				}else{
					draw_circle (eshot[i][0], eshot[i][1], 3, color3);
				}
			}
		}

		//当たり判定
		for(i = 0; i < 5; i++){
			if((pshot[i][0] != 0) && (pshot[i][1] != 0)){
				if((pshot[i][1] >= 7) && (pshot[i][1] <= 23)){
					if(crash (xe, pshot[i][0]) == 1){
						delete (xe, ye);
						end = 1;
					}
				}
			}
		}

		for(i = 0; i < 5; i++){
			if((eshot[i][0] != 0) && (eshot[i][1] != 0)){
				if((eshot[i][1] >= 137) && (eshot[i][1] <= 153)){
					if(crash (xp, eshot[i][0]) == 1){
						delete (xp, yp);
						end = 2;
					}
				}
			}
		}
		//時間稼ぎ
		for(i = 0; i<10000; i++){
		}
		if(end > 0){
			break;
		}
	}
	
	while(1){
		if(end == 1){//CLEAR
			ptr = (hword*)0x06000000;
			for(i = 0;i < 38400;i++){
				*ptr = color2;
				ptr += VRAM1;
			}
		}else if(end == 2){//GAMEOVER
			ptr = (hword*)0x06000000;
			for(i = 0;i < 38400;i++){
				*ptr = color3;
				ptr += VRAM1;
			}
		}
		//STARTで再起動
		ptr = (hword*)0x04000130;
		if((*ptr & 0x0008) != 0x0008){//右
			if(end == 1){
				main2();
			}else{
				main();
			}
		}
	}
	
	while(1);
	return 0;
}

void draw_point (hword x, hword y, hword color){
	hword *point;
	point = (hword*)0x06000000;
	point += VRAM1 * x + VRAM2 * y;
	*point = color;
}

void draw_circle (hword x, hword y, hword r, hword color){
	int i;
	int j;
	hword *point;
	for(i = -10; i < 10; i++){
		for(j = -10; j < 10; j++){
			if((j * j) + (i * i) <= (r * r)){
				point = (hword*)0x06000000;
				point += VRAM1 * (x + i) + VRAM2 * (y + j);
				*point = color;
			}
		}
	}
}	

void draw_rect (hword xa, hword ya, hword xb, hword yb, hword color){
	hword temp;
	hword i;
	hword j;

	if(xa > xb){
		temp = xb;
		xb = xa;
		xa = temp;
	}
	if(ya > yb){
		temp = yb;
		yb = ya;
		ya = temp;
	}

	for(i = xa; i <= xb; i++){
		for(j = ya; j <= yb; j++){
			draw_point (i, j, color);
		}
	}
}

void draw_player (hword x, hword y, hword color,int shape[11][11]){	
	hword *point;
	int i;
	int j;

	for(i = 0; i < 11; i++){
		for(j = 0; j < 11; j++){
			if(shape[i][j] == 1){
				point = (hword*)0x06000000;
				point += VRAM1 * (x - 5 + i) + VRAM2 * (y - 5 + j);
				*point = color;
			}
		}
	}
}

void draw_enemy (hword x, hword y, hword color,int shape[11][11]){
	hword *point;
	int i;
	int j;

	for(i = 0; i < 11; i++){
		for(j = 0; j < 11; j++){
			if(shape[i][j] == 1){
				point = (hword*)0x06000000;
				point += VRAM1 * (x - 5 + i) + VRAM2 * (y - 5 + j);
				*point = color;
			}
		}
	}
}

void delete (hword x, hword y){
	hword color1;
	hword color2;
	hword i;
	color1 = PLACL;
	color2 = BACKC;	
	draw_rect (x - 5, y - 5, x + 5, y + 5, color2);
 	draw_circle (x, y, 5, color1);
	for(i = 0; i < 25000; i++){
	}
	draw_circle (x + 2, y + 2, 2, color2);
	for(i = 0; i < 25000; i++){	}
	draw_circle (x + 1, y + 1, 4, color2);
}

hword crash (hword x, hword s){
	hword i;
	hword j;
	for(i = x - 5; i <= x + 5; i++){
		for(j = s - 3; j <= s + 3; j++){
			if(i == j){
				return 1;
			}
		}
	}
	return 0;
}

hword countUp1 (hword n){
	if(n == 4){
		return 0;
	}else{
		return ++n;
	}
}

hword countUp2 (hword n){
	if(n == 9){
		return 0;
	}else{
		return ++n;
	}
}

hword countUp3 (hword n){
	if(n == 14){
		return 0;
	}else{
		return ++n;
	}
}

int main2 (void){
	hword *ptr;
	hword xp;//Playerのx座標
	hword yp;//Playerのy座標
	hword xpv;//Playerのxの速さ
	hword xe;//Enemyのx座標
	hword ye;//Enemyのy座標
	hword xev;//Enemyのxの速さ
	hword pshot[5][2];//プレイヤーの弾[x座標、y座標]
	hword eshot[10][2];//敵の弾[x座標、y座標]
	hword shot_v;//自弾の速さ
	hword shot_ve;//敵に弾の速さ
	hword pshotNow;//next
	hword eshotNow;//next
	hword color1;//BACKC
	hword color2;//PLACL
	hword color3;//ENECL
	hword end;
	hword a;
	hword b;
	hword c;
	hword d;
	hword e;
	hword i;
	hword j;
	int playerShape[11][11];
	int enemyShape[11][11];
	
	//初期化
	xp = 120;
	yp = 145;
	xpv = 5;
	xe = 120;
	ye = 15;
	xev = 8;
	shot_v = 5;
	shot_ve = 8;
	for(i = 0; i < 5; i++){
		pshot[i][0] = 0;
		pshot[i][1] = 0;		
	}
	for(i = 0; i < 10; i++){
		eshot[i][0] = 0;
		eshot[i][1] = 0;
	}
	pshotNow = 0;
	eshotNow = 0;
	color1 = BACKC;
	color2 = PLACL;
	color3 = ENECL;
	end = 0;
	c = 0;
	d = 0;
	e = 0;
	for(i = 0; i < 11; i++){
		for(j = 0; j < 11; j++){
			playerShape[i][j] = 0;
		}
	}
	playerShape[1][6] = 1;
	playerShape[1][7] = 1;
	playerShape[1][8] = 1;
	playerShape[1][9] = 1;
	playerShape[2][4] = 1;
	playerShape[2][5] = 1;
	playerShape[2][6] = 1;
	playerShape[2][7] = 1;
	playerShape[2][8] = 1;
	playerShape[2][9] = 1;
	playerShape[2][10] = 1;
	playerShape[3][7] = 1;
	playerShape[3][8] = 1;
	playerShape[4][3] = 1;
	playerShape[4][4] = 1;
	playerShape[4][5] = 1;
	playerShape[4][6] = 1;
	playerShape[4][7] = 1;
	playerShape[4][8] = 1;
	playerShape[4][9] = 1;
	playerShape[4][10] = 1;
	playerShape[5][1] = 1;
	playerShape[5][2] = 1;
	playerShape[5][3] = 1;
	playerShape[5][7] = 1;
	playerShape[5][8] = 1;
	playerShape[5][9] = 1;
	playerShape[5][10] = 1;
	playerShape[9][6] = 1;
	playerShape[9][7] = 1;
	playerShape[9][8] = 1;
	playerShape[9][9] = 1;
	playerShape[8][4] = 1;
	playerShape[8][5] = 1;
	playerShape[8][6] = 1;
	playerShape[8][7] = 1;
	playerShape[8][8] = 1;
	playerShape[8][9] = 1;
	playerShape[8][10] = 1;
	playerShape[7][7] = 1;
	playerShape[7][8] = 1;
	playerShape[6][3] = 1;
	playerShape[6][4] = 1;
	playerShape[6][5] = 1;
	playerShape[6][6] = 1;
	playerShape[6][7] = 1;
	playerShape[6][8] = 1;
	playerShape[6][9] = 1;
	playerShape[6][10] = 1;

	for(i = 0; i < 11; i++){
		for(j = 0; j < 11; j++){
			enemyShape[i][j] = 0;
		}
	}
	enemyShape[1][5] = 1;
	enemyShape[1][6] = 1;
	enemyShape[1][9] = 1;
	enemyShape[2][4] = 1;
	enemyShape[2][5] = 1;
	enemyShape[2][6] = 1;
	enemyShape[2][8] = 1;
	enemyShape[3][3] = 1;
	enemyShape[3][4] = 1;
	enemyShape[3][6] = 1;
	enemyShape[3][7] = 1;
	enemyShape[3][9] = 1;
	enemyShape[4][2] = 1;
	enemyShape[4][3] = 1;
	enemyShape[4][4] = 1;
	enemyShape[4][5] = 1;
	enemyShape[4][6] = 1;
	enemyShape[4][8] = 1;
	enemyShape[5][2] = 1;
	enemyShape[5][3] = 1;
	enemyShape[5][4] = 1;
	enemyShape[5][5] = 1;
	enemyShape[5][6] = 1;
	enemyShape[5][7] = 1;
	enemyShape[9][5] = 1;
	enemyShape[9][6] = 1;
	enemyShape[9][9] = 1;
	enemyShape[8][4] = 1;
	enemyShape[8][5] = 1;
	enemyShape[8][6] = 1;
	enemyShape[8][8] = 1;
	enemyShape[7][3] = 1;
	enemyShape[7][4] = 1;
	enemyShape[7][6] = 1;
	enemyShape[7][7] = 1;
	enemyShape[7][9] = 1;
	enemyShape[6][2] = 1;
	enemyShape[6][3] = 1;
	enemyShape[6][4] = 1;
	enemyShape[6][5] = 1;
	enemyShape[6][6] = 1;
	enemyShape[6][8] = 1;


	//背景の塗りつぶし
	ptr = (hword*)0x06000000;
	for(i = 0; i < 38400; i++){
		*ptr = color1;
		ptr += VRAM1;
	}
	draw_player (xp, yp, color2, playerShape);
	while(1){
		//ボタン操作
		ptr = (hword*)0x04000130;
		if((*ptr & 0x0010) != 0x0010){//右
			if(xp <= 230){
				draw_player (xp, yp, color1, playerShape);
				xp = xp + xpv;
				draw_player (xp, yp, color2, playerShape);
				c++;
			}
		}else if((*ptr & 0x0020)!=0x0020){//左
			if(xp >= 7){
				draw_player (xp, yp, color1, playerShape);
				xp = xp - xpv;
				draw_player (xp, yp, color2, playerShape);
				d += 2;
			}
		}

		if((*ptr & 0x0001) != 0x0001){//A
			if(pshot[pshotNow][0] == 0){
				pshot[pshotNow][0] = xp;
				pshot[pshotNow][1] = yp - 10;
				pshotNow = countUp1 (pshotNow);
				e += 5;
			}
		}

		//敵の動き
		a = 0;
		b = 0;
		for(i = 0; i < 5; i++){
			if((pshot[i][0] != 0) && (pshot[i][1] != 0)){
				a += pshot[i][0];
				b++;
			}
		}
		if(a < (120 * b)){
			if(xe <= 226){
				draw_enemy (xe, ye, color1, enemyShape);
				xe = xe + xev;
				draw_enemy (xe, ye, color3, enemyShape);
			}else if(xe >= 13){
				draw_enemy (xe, ye, color1, enemyShape);
				xe = xe - xev;
				draw_enemy (xe, ye, color3, enemyShape);
			}
		}else if(a > (120 * b)){
			if(xe >= 13){
				draw_enemy (xe, ye, color1, enemyShape);
				xe = xe - xev;
				draw_enemy (xe, ye, color3, enemyShape);
			}else if(xe <= 226){
				draw_enemy (xe, ye, color1, enemyShape);
				xe = xe + xev;
				draw_enemy (xe, ye, color3, enemyShape);
			}
		}else{
			if((c + d + e) % 2 == 0){
				if(xe <= 226){
				draw_enemy (xe, ye, color1, enemyShape);
				xe = xe + xev;
				draw_enemy (xe, ye, color3, enemyShape);
				}
			}else{
				if(xe >= 13){
					draw_enemy (xe, ye, color1, enemyShape);
					xe = xe - xev;
					draw_enemy (xe, ye, color3, enemyShape);
				}
			}
		}
		if((c + d + e) % 3 == 0){
			if(eshot[eshotNow][0] == 0){
				eshot[eshotNow][0] = xe;
				eshot[eshotNow][1] = ye + 10;
				eshotNow = countUp2 (eshotNow);
			}
		}

		//弾を動かす
		for(i = 0; i < 5; i++){
			if((pshot[i][0] != 0) && (pshot[i][1] != 0)){
				draw_circle (pshot[i][0], pshot[i][1], 3, color1);
				pshot[i][1] = pshot[i][1] - shot_v;
				if(pshot[i][1] <= 3){
					pshot[i][0] = 0;
					pshot[i][1] = 0;
				}else{
					draw_circle (pshot[i][0], pshot[i][1], 3, color2);
				}
			}
		}

		for(i = 0; i < 10; i++){
			if((eshot[i][0] != 0) && (eshot[i][1] != 0)){
				draw_circle (eshot[i][0], eshot[i][1], 3, color1);
				eshot[i][1] = eshot[i][1] + shot_v;
				if(eshot[i][1] >= 157){
					eshot[i][0] = 0;
					eshot[i][1] = 0;
				}else{
					draw_circle (eshot[i][0], eshot[i][1], 3, color3);
				}
			}
		}

		//当たり判定
		for(i = 0; i < 5; i++){
			if((pshot[i][0] != 0) && (pshot[i][1] != 0)){
				if((pshot[i][1] >= 7) && (pshot[i][1] <= 23)){
					if(crash (xe, pshot[i][0]) == 1){
						delete (xe, ye);
						end = 1;
					}
				}
			}
		}

		for(i = 0; i < 10; i++){
			if((eshot[i][0] != 0) && (eshot[i][1] != 0)){
				if((eshot[i][1] >= 137) && (eshot[i][1] <= 153)){
					if(crash (xp, eshot[i][0]) == 1){
						delete (xp, yp);
						end = 2;
					}
				}
			}
		}
		//時間稼ぎ
		for(i = 0; i<10000; i++){
		}
		if(end > 0){
			break;
		}
	}
	
	while(1){
		if(end == 1){//CLEAR
			ptr = (hword*)0x06000000;
			for(i = 0;i < 38400;i++){
				*ptr = color2;
				ptr += VRAM1;
			}
		}else if(end == 2){//GAMEOVER
			ptr = (hword*)0x06000000;
			for(i = 0;i < 38400;i++){
				*ptr = color3;
				ptr += VRAM1;
			}
		}
		//STARTで再起動
		ptr = (hword*)0x04000130;
		if((*ptr & 0x0008) != 0x0008){//右
			if(end == 1){
				main3();
			}else{
				main();
			}
		}
	}

	while(1);
	return 0;
}	 

int main3 (void){
	hword *ptr;
	hword xp;//Playerのx座標
	hword yp;//Playerのy座標
	hword xpv;//Playerのxの速さ
	hword xe;//Enemyのx座標
	hword ye;//Enemyのy座標
	hword xev;//Enemyのxの速さ
	hword pshot[5][2];//プレイヤーの弾[x座標、y座標]
	hword eshot[15][2];//敵の弾[x座標、y座標]
	hword shot_v;//自弾の速さ
	hword shot_ve;//敵に弾の速さ
	hword pshotNow;//next
	hword eshotNow;//next
	hword color1;//BACKC
	hword color2;//PLACL
	hword color3;//ENECL
	hword end;
	hword a;
	hword b;
	hword c;
	hword d;
	hword e;
	hword i;
	hword j;
	int playerShape[11][11];
	int enemyShape[11][11];
	
	//初期化
	xp = 120;
	yp = 145;
	xpv = 5;
	xe = 120;
	ye = 15;
	xev = 12;
	shot_v = 5;
	shot_ve = 12;
	for(i = 0; i < 5; i++){
		pshot[i][0] = 0;
		pshot[i][1] = 0;		
	}
	for(i = 0; i < 15; i++){
		eshot[i][0] = 0;
		eshot[i][1] = 0;
	}
	pshotNow = 0;
	eshotNow = 0;
	color1 = BACKC;
	color2 = PLACL;
	color3 = ENECL;
	end = 0;
	c = 0;
	d = 0;
	e = 0;
	for(i = 0; i < 11; i++){
		for(j = 0; j < 11; j++){
			playerShape[i][j] = 0;
		}
	}
	playerShape[1][6] = 1;
	playerShape[1][7] = 1;
	playerShape[1][8] = 1;
	playerShape[1][9] = 1;
	playerShape[2][4] = 1;
	playerShape[2][5] = 1;
	playerShape[2][6] = 1;
	playerShape[2][7] = 1;
	playerShape[2][8] = 1;
	playerShape[2][9] = 1;
	playerShape[2][10] = 1;
	playerShape[3][7] = 1;
	playerShape[3][8] = 1;
	playerShape[4][3] = 1;
	playerShape[4][4] = 1;
	playerShape[4][5] = 1;
	playerShape[4][6] = 1;
	playerShape[4][7] = 1;
	playerShape[4][8] = 1;
	playerShape[4][9] = 1;
	playerShape[4][10] = 1;
	playerShape[5][1] = 1;
	playerShape[5][2] = 1;
	playerShape[5][3] = 1;
	playerShape[5][7] = 1;
	playerShape[5][8] = 1;
	playerShape[5][9] = 1;
	playerShape[5][10] = 1;
	playerShape[9][6] = 1;
	playerShape[9][7] = 1;
	playerShape[9][8] = 1;
	playerShape[9][9] = 1;
	playerShape[8][4] = 1;
	playerShape[8][5] = 1;
	playerShape[8][6] = 1;
	playerShape[8][7] = 1;
	playerShape[8][8] = 1;
	playerShape[8][9] = 1;
	playerShape[8][10] = 1;
	playerShape[7][7] = 1;
	playerShape[7][8] = 1;
	playerShape[6][3] = 1;
	playerShape[6][4] = 1;
	playerShape[6][5] = 1;
	playerShape[6][6] = 1;
	playerShape[6][7] = 1;
	playerShape[6][8] = 1;
	playerShape[6][9] = 1;
	playerShape[6][10] = 1;

	for(i = 0; i < 11; i++){
		for(j = 0; j < 11; j++){
			enemyShape[i][j] = 0;
		}
	}
	enemyShape[0][4] = 1;
	enemyShape[0][5] = 1;
	enemyShape[0][6] = 1;
	enemyShape[0][7] = 1;
	enemyShape[0][10] = 1;
	enemyShape[1][3] = 1;
	enemyShape[1][4] = 1;
	enemyShape[1][5] = 1;
	enemyShape[1][6] = 1;
	enemyShape[1][7] = 1;
	enemyShape[1][10] = 1;
	enemyShape[2][3] = 1;
	enemyShape[2][4] = 1;
	enemyShape[2][6] = 1;
	enemyShape[2][7] = 1;
	enemyShape[2][9] = 1;
	enemyShape[3][2] = 1;
	enemyShape[3][3] = 1;
	enemyShape[3][4] = 1;
	enemyShape[3][6] = 1;
	enemyShape[3][7] = 1;
	enemyShape[3][8] = 1;
	enemyShape[3][9] = 1;
	enemyShape[4][2] = 1;
	enemyShape[4][3] = 1;
	enemyShape[4][4] = 1;
	enemyShape[4][5] = 1;
	enemyShape[4][6] = 1;
	enemyShape[4][7] = 1;
	enemyShape[4][8] = 1;
	enemyShape[5][2] = 1;
	enemyShape[5][3] = 1;
	enemyShape[5][4] = 1;
	enemyShape[5][5] = 1;
	enemyShape[5][6] = 1;
	enemyShape[5][7] = 1;
	enemyShape[5][9] = 1;
	enemyShape[10][4] = 1;
	enemyShape[10][5] = 1;
	enemyShape[10][6] = 1;
	enemyShape[10][7] = 1;
	enemyShape[10][10] = 1;
	enemyShape[9][3] = 1;
	enemyShape[9][4] = 1;
	enemyShape[9][5] = 1;
	enemyShape[9][6] = 1;
	enemyShape[9][7] = 1;
	enemyShape[9][10] = 1;
	enemyShape[8][3] = 1;
	enemyShape[8][4] = 1;
	enemyShape[8][6] = 1;
	enemyShape[8][7] = 1;
	enemyShape[8][9] = 1;
	enemyShape[7][2] = 1;
	enemyShape[7][3] = 1;
	enemyShape[7][4] = 1;
	enemyShape[7][6] = 1;
	enemyShape[7][7] = 1;
	enemyShape[7][8] = 1;
	enemyShape[7][9] = 1;
	enemyShape[6][2] = 1;
	enemyShape[6][3] = 1;
	enemyShape[6][4] = 1;
	enemyShape[6][5] = 1;
	enemyShape[6][6] = 1;
	enemyShape[6][7] = 1;
	enemyShape[6][8] = 1;

	//背景の塗りつぶし
	ptr = (hword*)0x06000000;
	for(i = 0; i < 38400; i++){
		*ptr = color1;
		ptr += VRAM1;
	}
	draw_player (xp, yp, color2, playerShape);
	while(1){
		//ボタン操作
		ptr = (hword*)0x04000130;
		if((*ptr & 0x0010) != 0x0010){//右
			if(xp <= 230){
				draw_player (xp, yp, color1, playerShape);
				xp = xp + xpv;
				draw_player (xp, yp, color2, playerShape);
				c++;
			}
		}else if((*ptr & 0x0020)!=0x0020){//左
			if(xp >= 7){
				draw_player (xp, yp, color1, playerShape);
				xp = xp - xpv;
				draw_player (xp, yp, color2, playerShape);
				d += 2;
			}
		}

		if((*ptr & 0x0001) != 0x0001){//A
			if(pshot[pshotNow][0] == 0){
				pshot[pshotNow][0] = xp;
				pshot[pshotNow][1] = yp - 10;
				pshotNow = countUp1 (pshotNow);
				e += 5;
			}
		}

		//敵の動き
		a = 0;
		b = 0;
		for(i = 0; i < 5; i++){
			if((pshot[i][0] != 0) && (pshot[i][1] != 0)){
				a += pshot[i][0];
				b++;
			}
		}
		if(a < (120 * b)){
			if(xe <= 226){
				draw_enemy (xe, ye, color1, enemyShape);
				xe = xe + xev;
				draw_enemy (xe, ye, color3, enemyShape);
			}else if(xe >= 13){
				draw_enemy (xe, ye, color1, enemyShape);
				xe = xe - xev;
				draw_enemy (xe, ye, color3, enemyShape);
			}
		}else if(a > (120 * b)){
			if(xe >= 13){
				draw_enemy (xe, ye, color1, enemyShape);
				xe = xe - xev;
				draw_enemy (xe, ye, color3, enemyShape);
			}else if(xe <= 226){
				draw_enemy (xe, ye, color1, enemyShape);
				xe = xe + xev;
				draw_enemy (xe, ye, color3, enemyShape);
			}
		}else{
			if((c + d + e) % 2 == 0){
				if(xe <= 226){
				draw_enemy (xe, ye, color1, enemyShape);
				xe = xe + xev;
				draw_enemy (xe, ye, color3, enemyShape);
				}
			}else{
				if(xe >= 13){
					draw_enemy (xe, ye, color1, enemyShape);
					xe = xe - xev;
					draw_enemy (xe, ye, color3, enemyShape);
				}
			}
		}
		if((c + d + e) % 3 != 0){
			if(eshot[eshotNow][0] == 0){
				eshot[eshotNow][0] = xe;
				eshot[eshotNow][1] = ye + 10;
				eshotNow = countUp3 (eshotNow);
			}
		}







		//弾を動かす
		for(i = 0; i < 5; i++){
			if((pshot[i][0] != 0) && (pshot[i][1] != 0)){
				draw_circle (pshot[i][0], pshot[i][1], 3, color1);
				pshot[i][1] = pshot[i][1] - shot_v;
				if(pshot[i][1] <= 3){
					pshot[i][0] = 0;
					pshot[i][1] = 0;
				}else{
					draw_circle (pshot[i][0], pshot[i][1], 3, color2);
				}
			}
		}

		for(i = 0; i < 15; i++){
			if((eshot[i][0] != 0) && (eshot[i][1] != 0)){
				draw_circle (eshot[i][0], eshot[i][1], 3, color1);
				eshot[i][1] = eshot[i][1] + shot_v;
				if(eshot[i][1] >= 157){
					eshot[i][0] = 0;
					eshot[i][1] = 0;
				}else{
					draw_circle (eshot[i][0], eshot[i][1], 3, color3);
				}
			}
		}

		//当たり判定
		for(i = 0; i < 5; i++){
			if((pshot[i][0] != 0) && (pshot[i][1] != 0)){
				if((pshot[i][1] >= 7) && (pshot[i][1] <= 23)){
					if(crash (xe, pshot[i][0]) == 1){
						delete (xe, ye);
						end = 1;
					}
				}
			}
		}

		for(i = 0; i < 15; i++){
			if((eshot[i][0] != 0) && (eshot[i][1] != 0)){
				if((eshot[i][1] >= 137) && (eshot[i][1] <= 153)){
					if(crash (xp, eshot[i][0]) == 1){
						delete (xp, yp);
						end = 2;
					}
				}
			}
		}
		//時間稼ぎ
		for(i = 0; i<1000; i++){
		}
		if(end > 0){
			break;
		}
	}
	
	while(1){
		if(end == 1){//CLEAR
			ptr = (hword*)0x06000000;
			for(i = 0;i < 38400;i++){
				*ptr = color2;
				ptr += VRAM1;
			}
		}else if(end == 2){//GAMEOVER
			ptr = (hword*)0x06000000;
			for(i = 0;i < 38400;i++){
				*ptr = color3;
				ptr += VRAM1;
			}
		}
		//STARTで再起動
		ptr = (hword*)0x04000130;
		if((*ptr & 0x0008) != 0x0008){//右
			if(end == 1){
				main4();
			}else{
				main2();
			}
		}
	}

	while(1);
	return 0;
}	 

int main4 (void){
	hword *ptr;
	hword xp;//Playerのx座標
	hword yp;//Playerのy座標
	hword xpv;//Playerのxの速さ
	hword e1[2];//Enemy1の座標
	hword e2[2];//Enemy2の座標
	hword xev;//Enemyのxの速さ
	hword pshot[5][2];//プレイヤーの弾[x座標、y座標]
	hword e1shot[10][2];//敵1の弾[x座標、y座標]
	hword e2shot[10][2];//敵2の弾[x座標、y座標]
	hword shot_v;//自弾の速さ
	hword shot_ve;//敵に弾の速さ
	hword pshotNow;//next
	hword e1shotNow;//next
	hword e2shotNow;//next
	hword color1;//BACKC
	hword color2;//PLACL
	hword color3;//ENECL
	hword end;
	hword a;
	hword b;
	hword c;
	hword d;
	hword e;
	hword i;
	hword j;
	hword e1flag;
	hword e2flag;
	int playerShape[11][11];
	int enemyShape[11][11];
	
	//初期化
	xp = 120;
	yp = 145;
	xpv = 5;
	e1[0] = 120;
	e1[1] = 15;
	e2[0] = 120;
	e2[1] = 30;
	xev = 12;
	shot_v = 5;
	shot_ve = 12;
	for(i = 0; i < 5; i++){
		pshot[i][0] = 0;
		pshot[i][1] = 0;		
	}
	for(i = 0; i < 10; i++){
		e1shot[i][0] = 0;
		e1shot[i][1] = 0;
	}
	for(i = 0; i < 10; i++){
		e2shot[i][0] = 0;
		e2shot[i][1] = 0;
	}
	pshotNow = 0;
	e1shotNow = 0;
	e2shotNow = 0;
	color1 = BACKC;
	color2 = PLACL;
	color3 = ENECL;
	end = 0;
	c = 0;
	d = 0;
	e = 0;
	e1flag = 0;
	e2flag = 0;
	for(i = 0; i < 11; i++){
		for(j = 0; j < 11; j++){
			playerShape[i][j] = 0;
		}
	}
	playerShape[1][6] = 1;
	playerShape[1][7] = 1;
	playerShape[1][8] = 1;
	playerShape[1][9] = 1;
	playerShape[2][4] = 1;
	playerShape[2][5] = 1;
	playerShape[2][6] = 1;
	playerShape[2][7] = 1;
	playerShape[2][8] = 1;
	playerShape[2][9] = 1;
	playerShape[2][10] = 1;
	playerShape[3][7] = 1;
	playerShape[3][8] = 1;
	playerShape[4][3] = 1;
	playerShape[4][4] = 1;
	playerShape[4][5] = 1;
	playerShape[4][6] = 1;
	playerShape[4][7] = 1;
	playerShape[4][8] = 1;
	playerShape[4][9] = 1;
	playerShape[4][10] = 1;
	playerShape[5][1] = 1;
	playerShape[5][2] = 1;
	playerShape[5][3] = 1;
	playerShape[5][7] = 1;
	playerShape[5][8] = 1;
	playerShape[5][9] = 1;
	playerShape[5][10] = 1;
	playerShape[9][6] = 1;
	playerShape[9][7] = 1;
	playerShape[9][8] = 1;
	playerShape[9][9] = 1;
	playerShape[8][4] = 1;
	playerShape[8][5] = 1;
	playerShape[8][6] = 1;
	playerShape[8][7] = 1;
	playerShape[8][8] = 1;
	playerShape[8][9] = 1;
	playerShape[8][10] = 1;
	playerShape[7][7] = 1;
	playerShape[7][8] = 1;
	playerShape[6][3] = 1;
	playerShape[6][4] = 1;
	playerShape[6][5] = 1;
	playerShape[6][6] = 1;
	playerShape[6][7] = 1;
	playerShape[6][8] = 1;
	playerShape[6][9] = 1;
	playerShape[6][10] = 1;

	for(i = 0; i < 11; i++){
		for(j = 0; j < 11; j++){
			enemyShape[i][j] = 0;
		}
	}
	enemyShape[0][4] = 1;
	enemyShape[0][5] = 1;
	enemyShape[0][6] = 1;
	enemyShape[0][7] = 1;
	enemyShape[0][10] = 1;
	enemyShape[1][3] = 1;
	enemyShape[1][4] = 1;
	enemyShape[1][5] = 1;
	enemyShape[1][6] = 1;
	enemyShape[1][7] = 1;
	enemyShape[1][10] = 1;
	enemyShape[2][3] = 1;
	enemyShape[2][4] = 1;
	enemyShape[2][6] = 1;
	enemyShape[2][7] = 1;
	enemyShape[2][9] = 1;
	enemyShape[3][2] = 1;
	enemyShape[3][3] = 1;
	enemyShape[3][4] = 1;
	enemyShape[3][6] = 1;
	enemyShape[3][7] = 1;
	enemyShape[3][8] = 1;
	enemyShape[3][9] = 1;
	enemyShape[4][2] = 1;
	enemyShape[4][3] = 1;
	enemyShape[4][4] = 1;
	enemyShape[4][5] = 1;
	enemyShape[4][6] = 1;
	enemyShape[4][7] = 1;
	enemyShape[4][8] = 1;
	enemyShape[5][2] = 1;
	enemyShape[5][3] = 1;
	enemyShape[5][4] = 1;
	enemyShape[5][5] = 1;
	enemyShape[5][6] = 1;
	enemyShape[5][7] = 1;
	enemyShape[5][9] = 1;
	enemyShape[10][4] = 1;
	enemyShape[10][5] = 1;
	enemyShape[10][6] = 1;
	enemyShape[10][7] = 1;
	enemyShape[10][10] = 1;
	enemyShape[9][3] = 1;
	enemyShape[9][4] = 1;
	enemyShape[9][5] = 1;
	enemyShape[9][6] = 1;
	enemyShape[9][7] = 1;
	enemyShape[9][10] = 1;
	enemyShape[8][3] = 1;
	enemyShape[8][4] = 1;
	enemyShape[8][6] = 1;
	enemyShape[8][7] = 1;
	enemyShape[8][9] = 1;
	enemyShape[7][2] = 1;
	enemyShape[7][3] = 1;
	enemyShape[7][4] = 1;
	enemyShape[7][6] = 1;
	enemyShape[7][7] = 1;
	enemyShape[7][8] = 1;
	enemyShape[7][9] = 1;
	enemyShape[6][2] = 1;
	enemyShape[6][3] = 1;
	enemyShape[6][4] = 1;
	enemyShape[6][5] = 1;
	enemyShape[6][6] = 1;
	enemyShape[6][7] = 1;
	enemyShape[6][8] = 1;

	//背景の塗りつぶし
	ptr = (hword*)0x06000000;
	for(i = 0; i < 38400; i++){
		*ptr = color1;
		ptr += VRAM1;
	}
	draw_player (xp, yp, color2, playerShape);
	while(1){
		//ボタン操作
		ptr = (hword*)0x04000130;
		if((*ptr & 0x0010) != 0x0010){//右
			if(xp <= 230){
				draw_player (xp, yp, color1, playerShape);
				xp = xp + xpv;
				draw_player (xp, yp, color2, playerShape);
				c++;
			}
		}else if((*ptr & 0x0020)!=0x0020){//左
			if(xp >= 7){
				draw_player (xp, yp, color1, playerShape);
				xp = xp - xpv;
				draw_player (xp, yp, color2, playerShape);
				d += 2;
			}
		}

		if((*ptr & 0x0001) != 0x0001){//A
			if(pshot[pshotNow][0] == 0){
				pshot[pshotNow][0] = xp;
				pshot[pshotNow][1] = yp - 10;
				pshotNow = countUp1 (pshotNow);
				e += 5;
			}
		}

		//敵の動き
		if(e1flag == 0){
			a = 0;
			b = 0;
			for(i = 0; i < 5; i++){
				if((pshot[i][0] != 0) && (pshot[i][1] != 0)){
					a += pshot[i][0];
					b++;
				}
			}
			if(a < (120 * b)){
				if(e1[0] <= 226){
					draw_enemy (e1[0], e1[1], color1, enemyShape);
					e1[0] = e1[0] + xev;
					draw_enemy (e1[0], e1[1], color3, enemyShape);
				}else if(e1[0] >= 13){
					draw_enemy (e1[0], e1[1], color1, enemyShape);
					e1[0] = e1[0] - xev;
					draw_enemy (e1[0], e1[1], color3, enemyShape);
				}
			}else if(a > (120 * b)){
				if(e1[0] >= 13){
					draw_enemy(e1[0], e1[1], color1, enemyShape);
					e1[0] = e1[0] - xev;
					draw_enemy (e1[0], e1[1], color3, enemyShape);
				}else if(e1[0] <= 226){
					draw_enemy (e1[0], e1[1], color1, enemyShape);
					e1[0] = e1[0] + xev;
					draw_enemy (e1[0], e1[1], color3, enemyShape);
				}
			}else{
				if((c + d + e) % 2 == 0){
					if(e1[0] <= 226){
					draw_enemy (e1[0], e1[1], color1, enemyShape);
					e1[0] = e1[0] + xev;
					draw_enemy (e1[0], e1[1], color3, enemyShape);
					}
				}else{
					if(e1[0] >= 13){
						draw_enemy (e1[0], e1[1], color1, enemyShape);
						e1[0] = e1[0] - xev;
						draw_enemy (e1[0], e1[1], color3, enemyShape);
					}
				}
			}
			if((c + d + e) % 3 != 0){
				if(e1shot[e1shotNow][0] == 0){
					e1shot[e1shotNow][0] = e1[0];
					e1shot[e1shotNow][1] = e1[1] + 10;
					e1shotNow = countUp2 (e1shotNow);
				}
			}
			for(i = 0; i < 5; i++){
				if((pshot[i][0] != 0) && (pshot[i][1] != 0)){
					if((pshot[i][1] >= 7) && (pshot[i][1] <= 23)){
						if(crash (e1[0], pshot[i][0]) == 1){
							delete (e1[0], e1[1]);
							draw_rect (e1[0] - 5, e1[1] - 5, e1[0] + 5, e1[1] + 5, color1);
							end += 1;
							e1flag = 5;
						}
					}
				}
			}
		}



		if(e2flag == 0){
			a = 0;
			b = 0;
			for(i = 0; i < 5; i++){
				if((pshot[i][0] != 0) && (pshot[i][1] != 0)){
					a += pshot[i][0];
					b++;
				}
			}
			if(a > (120 * b)){
				if(e2[0] <= 226){
					draw_enemy (e2[0], e2[1], color1, enemyShape);
					e2[0] = e2[0] + xev;
					draw_enemy (e2[0], e2[1], color3, enemyShape);
				}else if(e2[0] >= 13){
					draw_enemy (e2[0], e2[1], color1, enemyShape);
					e2[0] = e2[0] - xev;
					draw_enemy (e2[0], e2[1], color3, enemyShape);
				}
			}else if(a < (120 * b)){
				if(e2[0] >= 13){
					draw_enemy(e2[0], e2[1], color1, enemyShape);
					e2[0] = e2[0] - xev;
					draw_enemy (e2[0], e2[1], color3, enemyShape);
				}else if(e2[0] <= 226){
					draw_enemy (e2[0], e2[1], color1, enemyShape);
					e2[0] = e2[0] + xev;
					draw_enemy (e2[0], e2[1], color3, enemyShape);
				}
			}else{
				if((c + d + e) % 2 == 1){
					if(e2[0] <= 226){
					draw_enemy (e2[0], e2[1], color1, enemyShape);
					e2[0] = e2[0] + xev;
					draw_enemy (e2[0], e2[1], color3, enemyShape);
					}
				}else{
					if(e2[0] >= 13){
						draw_enemy (e2[0], e2[1], color1, enemyShape);
						e2[0] = e2[0] - xev;
						draw_enemy (e2[0], e2[1], color3, enemyShape);
					}
				}
			}
			if((c + d + e) % 3 != 1){
				if(e2shot[e2shotNow][0] == 0){
					e2shot[e2shotNow][0] = e2[0];
					e2shot[e2shotNow][1] = e2[1] + 10;
					e2shotNow = countUp2 (e2shotNow);
				}
			}
			for(i = 0; i < 5; i++){
				if((pshot[i][0] != 0) && (pshot[i][1] != 0)){
					if((pshot[i][1] >= 22) && (pshot[i][1] <= 38)){
						if(crash (e2[0], pshot[i][0]) == 1){
							delete (e2[0], e2[1]);
							draw_rect (e2[0] - 5, e2[1] - 5, e2[0] + 5, e2[1] + 5, color1);
							end += 1;
							e2flag = 5;
						}
					}
				}
			}
		}

		//弾を動かす
		for(i = 0; i < 5; i++){
			if((pshot[i][0] != 0) && (pshot[i][1] != 0)){
				draw_circle (pshot[i][0], pshot[i][1], 3, color1);
				pshot[i][1] = pshot[i][1] - shot_v;
				if(pshot[i][1] <= 3){
					pshot[i][0] = 0;
					pshot[i][1] = 0;
				}else{
					draw_circle (pshot[i][0], pshot[i][1], 3, color2);
				}
			}
		}
		for(i = 0; i < 10; i++){
			if((e1shot[i][0] != 0) && (e1shot[i][1] != 0)){
				draw_circle (e1shot[i][0], e1shot[i][1], 3, color1);
				e1shot[i][1] = e1shot[i][1] + shot_v;
				if(e1shot[i][1] >= 157){
					e1shot[i][0] = 0;
					e1shot[i][1] = 0;
				}else{
					draw_circle (e1shot[i][0], e1shot[i][1], 3, color3);
				}
			}
		}
		for(i = 0; i < 10; i++){
			if((e2shot[i][0] != 0) && (e2shot[i][1] != 0)){
				draw_circle (e2shot[i][0], e2shot[i][1], 3, color1);
				e2shot[i][1] = e2shot[i][1] + shot_v;
				if(e2shot[i][1] >= 157){
					e2shot[i][0] = 0;
					e2shot[i][1] = 0;
				}else{
					draw_circle (e2shot[i][0], e2shot[i][1], 3, color3);
				}
			}
		}

		//衝突判定	
		for(i = 0; i < 10; i++){
			if((e1shot[i][0] != 0) && (e1shot[i][1] != 0)){
				if((e1shot[i][1] >= 137) && (e1shot[i][1] <= 153)){
					if(crash (xp, e1shot[i][0]) == 1){
						delete (xp, yp);
						end += 3;
					}
				}
			}
		}
		for(i = 0; i < 10; i++){
			if((e2shot[i][0] != 0) && (e2shot[i][1] != 0)){
				if((e2shot[i][1] >= 137) && (e2shot[i][1] <= 153)){
					if(crash (xp, e2shot[i][0]) == 1){
						delete (xp, yp);
						end += 3;
					}
				}
			}
		}

		//時間稼ぎ
		for(i = 0; i<1000; i++){
		}
		if(end >= 2){
			break;
		}
	}
	
	while(1){
		if(end == 2){//CLEAR
			ptr = (hword*)0x06000000;
			for(i = 0;i < 38400;i++){
				*ptr = color2;
				ptr += VRAM1;
			}
		}else if(end != 2){//GAMEOVER
			ptr = (hword*)0x06000000;
			for(i = 0;i < 38400;i++){
				*ptr = color3;
				ptr += VRAM1;
			}
		}
		//STARTで再起動
		ptr = (hword*)0x04000130;
		if((*ptr & 0x0008) != 0x0008){//右
			if(end == 2){
				main4();
			}else{
				main3();
			}
		}
	}

	while(1);
	return 0;
}