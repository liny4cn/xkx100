//ROOM: /d/yanziwu/qingzong.c

inherit ROOM;
void create()
{
	set("short", "��ڣ");
	set("long",@LONG
�������������ư��ƣ���Ȼ��Ȼ���ʣ�ԭ������Ľ�����ҵ�Ĺ�أ�
��˵����������˾����ڴ��ˡ����ϳ�����ϸ��С�ݣ���˵���ֲݳ���
���̣�������ή���ƺ�����������һƬ��������޳��ڡ�
LONG );
	set("outdoors", "yanziwu");
	set("exits", ([
		"south" : __DIR__"zhulin3",
	]));
	set("no_clean_up", 0);
	set("coor/x", 850);
	set("coor/y", -1480);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}