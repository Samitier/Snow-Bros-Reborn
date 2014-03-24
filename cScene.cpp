#include "cScene.h"
#include "Globals.h"

cScene::cScene(void)
{
}

cScene::~cScene(void)
{
}

bool cScene::LoadLevel(int level)
{
	bool res;
	FILE *fd;
	char file[16];
	int i,j,px,py;
	char tile;
	float coordx_tile, coordy_tile;

	res=true;

	if(level<10) sprintf(file,"%s0%d%s",(char *)FILENAME_DIR,level,(char *)FILENAME_EXT);
	else		 sprintf(file,"%s%d%s",(char *)FILENAME_DIR,level,(char *)FILENAME_EXT);

	fd=fopen(file,"r");
	if(fd==NULL) return false;

	id_DL0=glGenLists(1);
	glNewList(id_DL0,GL_COMPILE);
		glBegin(GL_QUADS);
			glTexCoord2f(0      ,1.0f);	    glVertex2i(0						,0						 );
			glTexCoord2f(1.0f	,1.0f);	    glVertex2i(BLOCK_SIZE*SCENE_WIDTH	,0						 );
			glTexCoord2f(1.0f	,0);		glVertex2i(BLOCK_SIZE*SCENE_WIDTH	,BLOCK_SIZE*SCENE_HEIGHT);
			glTexCoord2f(0		,0);		glVertex2i(0						,BLOCK_SIZE*SCENE_HEIGHT);
		glEnd();
	glEndList();

	id_DL=glGenLists(1);
	glNewList(id_DL,GL_COMPILE);
		glBegin(GL_QUADS);
			
			fscanf(fd,"%c",&tile);//ignores first line of file(numEnemies)
			fscanf(fd,"%c",&tile);//and the /n

			for(j=SCENE_HEIGHT-1;j>=0;j--)
			{
				px=SCENE_Xo;
				py=SCENE_Yo+(j*TILE_SIZE);

				for(i=0;i<SCENE_WIDTH;i++)
				{
					fscanf(fd,"%c",&tile);
					if(tile ==',') fscanf(fd,"%c",&tile);
					if(tile =='0' || tile == 'e' || tile == 'a') {
						//Tiles must be != 0 !!!
						map[(j*SCENE_WIDTH)+i]=0;

					}
					else 
					{
						//Tiles = 1,2,3,...
						int t =tile-48;
						map[(j*SCENE_WIDTH)+i] = t;

						if(t ==1) {
							coordx_tile = 0.0f;
							coordy_tile = 0.0f;
						}else if(t==2) {
							coordx_tile = 0.5f;
							coordy_tile = 0.0f;
						}else if (t==3){
							coordx_tile = 0.0f;
							coordy_tile = 0.5f;
						}else if(t==4){
							coordx_tile = 0.5f;
							coordy_tile = 0.5f;
						}

						glTexCoord2f(coordx_tile       ,coordy_tile+0.5f);	    glVertex2i(px           ,py           );
						glTexCoord2f(coordx_tile+0.5f  ,coordy_tile+0.5f);	    glVertex2i(px+BLOCK_SIZE,py           );
						glTexCoord2f(coordx_tile+0.5f  ,coordy_tile       );	glVertex2i(px+BLOCK_SIZE,py+BLOCK_SIZE);
						glTexCoord2f(coordx_tile       ,coordy_tile     );	    glVertex2i(px           ,py+BLOCK_SIZE);
					}
					px+=TILE_SIZE;
				}
				fscanf(fd,"%c",&tile); //pass enter
			}

		glEnd();
	glEndList();

	fclose(fd);

	return res;
}

void cScene::Draw(int tex_id, int tex_id0)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex_id0);
	glCallList(id_DL0);
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glCallList(id_DL);
	glDisable(GL_TEXTURE_2D);
}
int* cScene::GetMap()
{
	return map;
}