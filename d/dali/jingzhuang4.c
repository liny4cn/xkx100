//Room: /d/dali/jingzhuang4.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","���Ĳ�");
	set("long",@LONG
���а����������Դ����ж�����������Ŀ���䣬�ݲ��ɱ档
�����������������ķ𾭡�����β�����С��ȼú���--�����ˡ���
����
LONG);
	set("exits",([ /* sizeof() == 1 */
	    "up"    : __DIR__"jingzhuang5",
	    "down"  : __DIR__"jingzhuang3",
	]));
	set("no_clean_up", 0);
	set("coor/x", -36000);
	set("coor/y", -70400);
	set("coor/z", 30);
	setup();
	replace_program(ROOM);
}