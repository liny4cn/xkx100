//Room: jsjdg3.c ��ʮ�ŵ���
//Date: Oct. 2 1997 by That

inherit ROOM;

void create()
{
	set("short","��ʮ�ŵ���");
	set("long",@LONG
���������ġ���ʮ�ŵ��ա�����·����������ǧ�۰ٻء���˵��ȥ���и�
������ķ�ɮ���ˣ���һ������·�������������������ǵ�֪�˴��о�����û
�󣬱���Ҳ���˸�������Ĳ�ľ�����ԡ����ӡ���֮���ɴ˶�����ǧ���֣���
����϶���
LONG);
	set("outdoors", "emei");
	set("exits",([ /* sizeof() == 1 */
		"northeast" : __DIR__"jsjdg2",
		"westup"    : __DIR__"jsjdg4",
	]));
	set("no_clean_up", 0);
	set("coor/x", -6160);
	set("coor/y", -1080);
	set("coor/z", 90);
	setup();
}

int valid_leave(object me, string dir)
{
	int c_exp,c_skill;

	if (dir == "westup" && userp(me))
	{
		c_exp=me->query("combat_exp");
		c_skill=me->query_skill("dodge",1);
		if ( me->query("qi") < 10 ) me->unconcious();
		else
		{
			me->receive_damage("qi", 10);
			if (((c_skill*c_skill*c_skill/10)< c_exp) &&
				(c_skill < 101))
				me->improve_skill("dodge", (int)me->query_skill("dodge", 1));
			tell_object(me,"���ؾ�ʮ�ŵ�������������һ�󣬾��ú��ۡ�\n");
		}
	}
	return 1;
}