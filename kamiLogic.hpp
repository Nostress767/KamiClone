std::ostream &operator<<(std::ostream &os, const SquareIndex& si){
	return os << si.row << ' ' << si.column << '\n';}
void Square::update_offsets(){
	xoffset = BOARD_X_OFFSET+(SQUARE_SIZE*index.column);
	yoffset = BOARD_Y_OFFSET+(SQUARE_SIZE*index.row);
	update_triangles();}
void Square::update_triangles(){
	triangles[3].v1.x = triangles[1].v2.x = triangles[1].v1.x = triangles[0].v1.x = xoffset;
	triangles[2].v1.y = triangles[1].v1.y = triangles[0].v2.y = triangles[0].v1.y = yoffset;
	triangles[3].v2.x = triangles[2].v2.x = triangles[2].v1.x = triangles[0].v2.x = xoffset + SQUARE_SIZE - PARITY;
	triangles[3].v2.y = triangles[2].v2.y = triangles[3].v1.y = triangles[1].v2.y = yoffset + SQUARE_SIZE - PARITY;

	triangles[0].v3.x = triangles[1].v3.x = triangles[2].v3.x = triangles[3].v3.x = xoffset + HALF_SQUARE;
	triangles[0].v3.y = triangles[1].v3.y = triangles[2].v3.y = triangles[3].v3.y = yoffset + HALF_SQUARE;}
void Square::update_color(olc::Pixel sqrcolor){
	color = sqrcolor;}
void Square::update_index(int rowindex, int columnindex){
	index.row = rowindex; index.column = columnindex;
	update_offsets();}
void Square::draw_square(olc::PixelGameEngine* pge){
	pge->FillRectDecal({SCf(xoffset), SCf(yoffset)}, {SCf(SQUARE_SIZE), SCf(SQUARE_SIZE)}, color);
	pge->DrawLineDecal({SCf(xoffset), SCf(yoffset)},{SCf(xoffset+SQUARE_SIZE), SCf(yoffset)}, olc::BLACK);
	pge->DrawLineDecal({SCf(xoffset), SCf(yoffset)},{SCf(xoffset), SCf(yoffset+SQUARE_SIZE)}, olc::BLACK);}
void Square::draw_triangle(olc::PixelGameEngine* pge, int tindex){
	olc::Pixel specific_color = olc::GREEN;
  if (tindex == 1){
    specific_color = olc::RED;
  } else if (tindex == 2){
    specific_color = olc::MAGENTA;
  } else if (tindex == 3){
    specific_color = olc::CYAN;
	}
	pge->FillTriangle(triangles[tindex].v1.x, triangles[tindex].v1.y, triangles[tindex].v2.x, triangles[tindex].v2.y, triangles[tindex].v3.x, triangles[tindex].v3.y, specific_color);}

// variables: xoffset yoffset textxoffset textyoffset ysize xsize color r_color
RectButton::RectButton(int vl,Px p,Px s,olc::Pixel c,std::string t,Px tp,olc::Pixel tc,Px ts,std::string a){
	value = vl;
	xoffset = p.x;
	yoffset = p.y;
	xsize = s.x;
	ysize = s.y;
	color = c;
	if (a=="NW"){
		textxoffset = xoffset+tp.x;
		textyoffset = yoffset+tp.y;
	} else if (a=="N"){
		textxoffset = xoffset+(xsize/2)+tp.x-((t.size()*(8*ts.x))/2);
		textyoffset = yoffset+tp.y;
	} else if (a=="NE"){
		textxoffset = xoffset+xsize+tp.x-(t.size()*(8*ts.x));
		textyoffset = yoffset+tp.y;
	} else if (a=="W"){
		textxoffset = xoffset+tp.x;
		textyoffset = yoffset+tp.y+(ysize/2)-(4*ts.y);
	} else if (a=="C"){
		textxoffset = xoffset+tp.x+(xsize/2)-(t.size()*(8*ts.x))/2;
		textyoffset = yoffset+tp.y+(ysize/2)-(4*ts.y);
	} else if (a=="E"){
		textxoffset = xoffset+tp.x+xsize-(t.size()*(8*ts.x));
		textyoffset = yoffset+tp.y+(ysize/2)-(4*ts.y);
	} else if (a=="SW"){
		textxoffset = xoffset+tp.x;
		textyoffset = yoffset+tp.y+ysize-(8*ts.y);
	} else if (a=="S"){
		textxoffset = xoffset+tp.x+(xsize/2)-(t.size()*(8*ts.x))/2;
		textyoffset = yoffset+tp.y+ysize-(8*ts.y);
	} else if (a=="SE"){
		textxoffset = xoffset+tp.x+xsize-(t.size()*(8*ts.x));
		textyoffset = yoffset+tp.y+ysize-(8*ts.y);
	} else{
		textxoffset = xoffset+tp.x;
		textyoffset = yoffset+tp.y;}
	text = t;
	textcolor = tc;
	textxscale = ts.x;
	textyscale = ts.y;}
XYRANGE RectButton::get_hitbox(){
	return {xoffset,xoffset+xsize-1,yoffset,yoffset+ysize-1};}
bool RectButton::is_inside(int x, int y){
	if (x<xoffset||x>xoffset+xsize-1||y<yoffset||y>yoffset+ysize-1) return false;
	return true;}
bool RectButton::is_inside(std::array<int,2> xy){
	if (xy[0]<xoffset||xy[0]>xoffset+xsize-1||xy[1]<yoffset||xy[1]>yoffset+ysize-1) return false;
	return true;}
void RectButton::update_pos(int x, int y){
	xoffset = x;
	yoffset = y;
	update_text_pos(0,0);}
void RectButton::update_text_pos(int x, int y){
	textxoffset = xoffset+x;
	textyoffset = yoffset+y;}
void RectButton::update_size(int x, int y){
	xsize = x;
	ysize = y;}
void RectButton::update_text(std::string& str){
	text = str;}
void RectButton::update_textcolor(olc::Pixel newcolor){
	textcolor = newcolor;}
void RectButton::update_color(olc::Pixel newcolor){
	color = newcolor;}
void RectButton::draw_button(olc::PixelGameEngine* pge){
	pge->FillRectDecal({SCf(xoffset),SCf(yoffset)},{SCf(xsize),SCf(ysize)},color);
	if (text!="") draw_text(pge);}
void RectButton::draw_text(olc::PixelGameEngine* pge){
	pge->DrawStringDecal({SCf(textxoffset),SCf(textyoffset)},text,textcolor,{SCf(textxscale),SCf(textyscale)});}

//bool main_menu = true;int LEVEL = 0;int ACOES = 0;int current_color = 1;renderboard;logicboard;
Game::Game(olc::PixelGameEngine* pge){
	pgeptr = pge;
	for(int i=0;i<SQUARE_Y_AMOUNT;i++){
		for(int j=0;j<SQUARE_X_AMOUNT;j++){
			renderboard[i][j].update_index(i,j);}}}
void Game::draw_board(){
	//Draw triangle test
	for (int i = 0; i < SQUARE_Y_AMOUNT; i++){
		for (int j=0; j < SQUARE_X_AMOUNT; j++){
			renderboard[i][j].draw_square(pgeptr);
			//kamiboard[i][j].draw_triangle(this,0);
			//kamiboard[i][j].draw_triangle(this,1);
			//kamiboard[i][j].draw_triangle(this,2);
			//kamiboard[i][j].draw_triangle(this,3);
		}}}
void Game::draw_buttons(){
	for(auto button: color_buttons){
		button.draw_button(pgeptr);}
}
void Game::update_mouse_pos(int x, int y){
	mouse_pos[0] = x;
	mouse_pos[1] = y;
	find_square();}
void Game::find_square(){
	if (mouse_pos[0] < BOARD_X_OFFSET){
		hovered_square_index.row = -1;
		hovered_square_index.column = -1;
	} else {
		int xcalculation = mouse_pos[0] - BOARD_X_OFFSET;
		int ycalculation = mouse_pos[1] - BOARD_Y_OFFSET;
		div_t column = div(xcalculation, SQUARE_SIZE);
		div_t row = div(ycalculation, SQUARE_SIZE);
// div_t result1 = div(100, 6);
// .quot and .rem
		hovered_square_index.row = row.quot;
		hovered_square_index.column = column.quot;}
	}
void Game::update_renderboard(){
	for(int i=0;i<SQUARE_Y_AMOUNT;i++){
		for(int j=0;j<SQUARE_X_AMOUNT;j++){
			renderboard[i][j].update_color(COLORS[logicboard[i][j]]);}}}
void Game::update_logicboard(LOGICBOARD newboard){
	logicboard = newboard;
	update_renderboard();}
void Game::load_level(int level){
	TABTUPLE temp = load_board(level);
	logicboard = std::get<3>(temp);
	current_level = std::get<0>(temp);
	n_actions = std::get<1>(temp);
	n_colors = std::get<2>(temp);
	update_renderboard();
	create_color_buttons();}
void Game::change_screen_to(int next_screen){current_screen=next_screen;}
bool Game::try_to_paint_square(){
	//
	if (pgeptr->GetMouse(LEFT_MOUSE).bPressed){
		if (hovered_square_index.row < 0 || hovered_square_index.column < 0){
			return false;
		} else {
			update_logicboard(paint(logicboard, hovered_square_index.row, hovered_square_index.column, current_color));
			return true;}
	}
	return false;}
bool Game::try_to_change_color(){
	for(auto button: color_buttons){
		if(button.is_inside(mouse_pos)&&pgeptr->GetMouse(LEFT_MOUSE).bPressed){
			current_color = button.value;
			return true;}}
	return false;
}
void Game::create_color_buttons(){
	for(int i=0;i<n_colors;i++){
		color_buttons.push_back(ColorButton(i+1,{0,(SCREEN_Y_SIZE/n_colors)*i},{BOARD_X_OFFSET-1,SCREEN_Y_SIZE/n_colors},COLORS[i+1]));}
}

MainMenu::MainMenu(olc::PixelGameEngine* pge,Game* gm){
	gameptr = gm;
	pgeptr = pge;
	int counter = 0;
	// Temporary non generic offsets
	std::array<int,5> abc = {SCREEN_X_SIZE/10,(SCREEN_X_SIZE/10)*4,(SCREEN_X_SIZE/10)*7,SCREEN_X_SIZE/10,(SCREEN_X_SIZE/10)*4};
	std::array<int,5> def = {(SCREEN_Y_SIZE/12)*1,(SCREEN_Y_SIZE/12)*1,(SCREEN_Y_SIZE/12)*1,(SCREEN_Y_SIZE/12)*6,(SCREEN_Y_SIZE/12)*6};
	for(int i=0;i<LEVELS_AMOUNT;i++){
		int xoffset = abc[i];
		int yoffset = def[i];
		int xsize = SCREEN_X_SIZE/5;
		int ysize = xsize;
		std::string bt = "Level ";
		bt.push_back(SCc(i+49));
		buttons.push_back(LevelButton(i,{xoffset,yoffset},{xsize,ysize},olc::GREEN,bt));}
		counter+=2;
}
void MainMenu::draw_buttons(){
	for(auto button: buttons){
		button.draw_button(pgeptr);}
}
bool MainMenu::try_to_load_level(){
	for(auto button: buttons){
		if (button.is_inside(gameptr->mouse_pos)&&pgeptr->GetMouse(LEFT_MOUSE).bPressed){
			gameptr->load_level(button.value);
			return true;}}
	return false;
}

int pow(int x, unsigned int p){
  if (p == 0) return 1;
  if (p == 1) return x;

  int tmp = pow(x, p/2);
  if (p%2 == 0) return tmp * tmp;
  else return x * tmp * tmp;}
void merge_edge(VNEIGHBORGRAPH &G, int i, int j){
	G[j].erase(i);
	G[i].erase(j);
	G[i].insert(G[j].begin(),G[j].end());
	for (auto v: G[j]){
		G[v].erase(j);
		G[v].insert(i);}
	G.erase(j);}
NCGRAPHPAIR generate_graph(LOGICBOARD T){
	VNEIGHBORGRAPH G;
	std::unordered_map<int,int> C;
	// 1Dindex
	// 1Dindex, {1Dindex of square 1 connected to it,1Dindex of square 2 connected to it}
	// 1Dindex, T[line of 1Dindex][column of 1Dindex]
	// Top left corner
	G.insert({0,{1,SQUARE_X_AMOUNT}});
	C.insert({0,T[0][0]});
	// Top right corner
	int k = SQUARE_X_AMOUNT-1;
	G.insert({k,{k-1,k+SQUARE_X_AMOUNT}});
	C.insert({k,T[0][SQUARE_X_AMOUNT-1]});
	// Bottom left corner
	k = (SQUARE_Y_AMOUNT-1)*SQUARE_X_AMOUNT;
	G.insert({k,{k-SQUARE_X_AMOUNT,k+1}});
	C.insert({k,T[SQUARE_Y_AMOUNT-1][0]});
	// Bottom right corner
	k = (SQUARE_Y_AMOUNT-1)*SQUARE_X_AMOUNT + SQUARE_X_AMOUNT-1;
	G.insert({k,{k-SQUARE_X_AMOUNT,k-1}});
	C.insert({k,T[SQUARE_Y_AMOUNT-1][SQUARE_X_AMOUNT-1]});
	// North edge
	for (int j = 0;j<SQUARE_X_AMOUNT;j++){
		k = j-1;
		G.insert({k,{k-1,k+1,k+SQUARE_X_AMOUNT}});
		C.insert({k,T[0][j]});}
	// West edge
	for (int i = 0;i<SQUARE_Y_AMOUNT;i++){
		k = (i-1)*SQUARE_X_AMOUNT;
		G.insert({k,{k-SQUARE_X_AMOUNT,k+1,k+SQUARE_X_AMOUNT}});
		C.insert({k,T[i][0]});}
	// East edge
	for (int i = 0;i<SQUARE_Y_AMOUNT;i++){
		k = (i-1)*SQUARE_X_AMOUNT+SQUARE_X_AMOUNT-1;
		G.insert({k,{k-SQUARE_X_AMOUNT,k-1,k+SQUARE_X_AMOUNT}});
		C.insert({k,T[i][SQUARE_X_AMOUNT-1]});}
	// South edge
	for (int j = 0;j<SQUARE_X_AMOUNT;j++){
		k = (SQUARE_Y_AMOUNT-1)*SQUARE_X_AMOUNT+j-1;
		G.insert({k,{k-SQUARE_X_AMOUNT,k-1,k+1}});
		C.insert({k,T[SQUARE_Y_AMOUNT-1][j]});}
	// Center
	for (int i=1;i<SQUARE_Y_AMOUNT-1;i++){
		for (int j=1;j<SQUARE_X_AMOUNT-1;j++){
			k = i*SQUARE_X_AMOUNT+j;
			G.insert({k,{k-SQUARE_X_AMOUNT,k-1,k+1,k+SQUARE_X_AMOUNT}});
			C.insert({k,T[i][j]});}}
	// Reduce graph by merging same-color neighbors
	bool colapsed = true;
	while (colapsed){
		colapsed = false;
		int U = 0;
		int V = 0;
		for (auto u: G){
			for (auto v: G[u.first]){
				if (C[u.first] == C[v]){U=u.first; V=v; colapsed = true; break;}}
			if (colapsed) break;}
		if (colapsed) {merge_edge(G, U, V); C.erase(V);}}
	return std::make_pair(G,C);}
NCGRAPHPAIR paint_vertex(VNEIGHBORGRAPH G,VCOLORGRAPH C,int n, int c){
	VNEIGHBORGRAPH Gp = G;
	VCOLORGRAPH Cp = C;
	Cp[n] = c;
	for (auto v: G[n]){
		if (C[v] == c){
			merge_edge(Gp,n,v);
			Cp.erase(v);}}
	return std::make_pair(Gp,Cp);}
TABTUPLE load_board(int level){
	LOGICBOARD temparray = {};

	std::array<int,5> metadata = {0, 0, 0, 0, 0}; // level, actions, sizeX, sizeY, colors

	int newline_counter = 0;
	int char_counter = 0;
	int number = 0;
	int numberpower = 0;
	int numbercounter = 0;

	while (newline_counter < SQUARE_Y_AMOUNT+1){
		char current_char = LEVELS[level][char_counter];
		char_counter++;
		if (current_char == '\n') {
			if (newline_counter == 0) metadata[numbercounter] = number;
			else temparray[newline_counter-1][numbercounter] = number;
			numbercounter=0; number = 0; numberpower = 0; newline_counter ++; continue;}
		if (current_char == ' ') {
			if (newline_counter == 0) metadata[numbercounter] = number;
			else temparray[newline_counter-1][numbercounter] = number;
			numbercounter++; number = 0; numberpower = 0; continue;}
		number = (number * pow(10, numberpower)) + SCi(current_char) - 48;
		numberpower++;}
  return {metadata[0], metadata[1], metadata[4], temparray};}
void burn(LOGICBOARD& array,int l,int c,int originalcolor){
	if (!(l<0||c<0||l>=SQUARE_Y_AMOUNT||c>=SQUARE_X_AMOUNT)) {
		if (array[l][c] > 0 && array[l][c] == originalcolor){
			array[l][c] = -1;
			burn(array,l-1,c,originalcolor);
			burn(array,l,c+1,originalcolor);
			burn(array,l+1,c,originalcolor);
			burn(array,l,c-1,originalcolor);}}}
LOGICBOARD paint(LOGICBOARD table, int line, int column, int color){
	burn(table,line,column,table[line][column]);
	for (int i=0;i<SQUARE_Y_AMOUNT;i++){
		for (int j=0;j<SQUARE_X_AMOUNT;j++){
			if (table[i][j] == -1) table[i][j] = color;}}
	return table;}
bool check_game_over(LOGICBOARD table){
	for (int i=0;i<SQUARE_Y_AMOUNT;i++){
		for (int j=0;j<SQUARE_X_AMOUNT;j++){
			if (table[i][j] != table[0][0]) return false;}}
	return true;}
std::array<int, 2> search(VNEIGHBORGRAPH L, VCOLORGRAPH C, int n_actions){
	std::array<int,2> deadend = {-1,-1};
	if (n_actions < 0) return deadend;
	if (L.size() == 1){
		int Lkey = 0;
		// map.first = key, map.second = value
		for( const VNPAIR& l : L ) {
    	Lkey = l.first;}
		return {Lkey,C[Lkey]};
	} else {
		for( const VNPAIR& l : L ) {
			for( const VCPAIR& c : C ) {
	    	if (l.first == c.first) continue;
				NCGRAPHPAIR newLC = paint_vertex(L,C,l.first,c.second);
				if (search(newLC.first,newLC.second,n_actions-1) == deadend) return {l.first,c.second};}}}
	return deadend;}
std::array<int,3> hint(LOGICBOARD T, int n_actions){
	NCGRAPHPAIR LC = generate_graph(T);
	std::array<int,2> nc = search(LC.first,LC.second,n_actions);
	if (nc[0] == -1 || nc[1] == -1) return {0,0,0};
	int i = nc[0] / SQUARE_X_AMOUNT; int j = nc[0] % SQUARE_X_AMOUNT;
	return {i,j,nc[1]};}
