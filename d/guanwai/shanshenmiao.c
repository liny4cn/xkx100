// /guanwai/shanshenmiao.c

inherit ROOM;

void create()
{
	set("short", "山神庙");
	set("long", @LONG
这是一个用木板和石头垒成的小庙，庙前地上散落着一些然过的灰
烬。庙里供奉着山神爷老把头的灵位 (lingwei)。传说他是所有采参人
的祖师爷，所以每个进山挖参的参客都要来这里祭拜，希望能得到他老
人家的保佑。
LONG );
	set("item_desc", ([
		"lingwei"  : 
"
**************
*            *
*     山     *
*     神     *
*     爷     *
*     老     *
*     把     *
*     头     *
*            *
*     孙     *
*     良     *
*            *
*     之     *
*     位     *
*            *
**************
"
	]));
	set("exits", ([
		"out"  : __DIR__"huandi2",
	]));
	set("objects", ([
		__DIR__"npc/yanji" : 1,
	]));
	set("outdoors", "guanwai");
	set("coor/x", 6080);
	set("coor/y", 5230);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}