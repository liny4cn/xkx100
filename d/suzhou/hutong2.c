// Room: /d/suzhou/hutong2.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
	set("short", "��ͬ");
	set("long", @LONG
����һ���ڰ��������С������з·�Ʈ����һ��������Ϣ��
������ü���۵ض������������������������������������һ��С�
��Ϊ���������
LONG );
	set("outdoors", "suzhou");
	set("no_clean_up", 0);
	set("exits", ([
		"north"     : __DIR__"leitai",
		"east"      : __DIR__"hutong3",
		"southwest" : __DIR__"hutong1",
	]));
	set("objects", ([
		"/d/city/npc/liumangtou" : 1,
		"/d/city/npc/liumang" : 2,
	]));
	set("coor/x", 870);
	set("coor/y", -990);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}