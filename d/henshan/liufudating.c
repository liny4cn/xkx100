// liufudating.c
// Date: Nov.1997 by Venus

#include <room.h>
inherit ROOM;
int do_knock(string arg);

void create()
{
        set("short", "��������");
        set("long", @LONG
����������Ͱ������ˡ���������̫ʦ���ϣ���ɫ�������Ա�����
һ���������ˣ������Եü�Ϊ���С�����ϥ�Ͽ���һ��СŮ����������
�з���һ�Ų輸���������˽��С�һֻ�����á������߰�Ļƽ����ӣ�
���ڲ輸֮�ϣ�������ʢ������ˮ��
LONG);
        set("exits", ([
            "west"   : __DIR__"liufuwest",
            "east"   : __DIR__"liufueast",
            "south"  : __DIR__"liufudayuan",
            "north"  : __DIR__"shanting",
        ]));
        set("objects", ([
                CLASS_D("henshan")+"/liu":1,
                __DIR__"npc/qu" : 1,
                __DIR__"npc/xiaoqu" : 1,
        ]));
//        set("no_clean_up", 0);
	set("coor/x", -400);
	set("coor/y", -1170);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}