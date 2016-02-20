// hp cmds (Mon 09-04-95)
// ������ʦ�쿴���������״̬�Ĺ��ܡ�
// Added by Spacenet@FXLT 1.18.2000 
inherit F_CLEAN_UP;
 
#include <ansi.h>
 

 
string status_color(int current, int max);
 
int main(object me, string arg)
{
	object ob;
	mapping my;
	int flag = 0;
 
	seteuid(getuid(me));
 
	if(!arg || arg == me->query("id"))
		ob = me;
	else
		{
			ob = present(arg, environment(me));
			if (!ob) ob = find_player(arg);
			if (!ob) ob = find_living(arg);
			if(wizardp(me))
			{
				if (!ob)
				{
					ob = new(USER_OB);
					seteuid(arg);
					export_uid(ob);
					flag = 1;
					if (!ob->restore())
					{
						destruct(ob);
						return notify_fail("û�������ҡ�\n");
					}
				}
			}
			else
			{
				if(!ob || !me->visible(ob)) return notify_fail("ֻ�ܲ쿴�Լ���״̬��\n");
				if(!ob->query("parents"))
					return notify_fail("ֻ����ʦ�ܲ쿴���˵�״̬��\n");
				else
					if(member_array(me->query("id"),ob->query("parents"))<=-1)
						return notify_fail("ֻ�е����ܲ쿴������״̬��\n");
			}
		}

	if (!ob->is_character())
		return notify_fail("�ǲ��ǻ��\n");

	my = ob->query_entire_dbase();
	printf(HIC"��"HIY"������������������������������������������������������������"HIC"��\n"NOR);
	printf(HIC"�� �� �� �� %s%4d/ %4d %s(%3d��)" HIC "   �� �� �� �� %s%4d / %4d (+%d)\n" NOR,
		status_color(my["jing"], my["eff_jing"]), my["jing"], my["eff_jing"],
		status_color(my["eff_jing"], my["max_jing"]),	my["eff_jing"] * 100 / my["max_jing"],
		status_color(my["jingli"], my["max_jingli"]),	my["jingli"], my["max_jingli"],
		my["jiajing"] );
	printf(HIC"�� �� Ѫ �� %s%4d/ %4d %s(%3d��)" HIC "   �� �� �� �� %s%4d / %4d (+%d)\n" NOR,
		status_color(my["qi"], my["eff_qi"]), my["qi"], my["eff_qi"],
		status_color(my["eff_qi"], my["max_qi"]), my["eff_qi"] * 100 / my["max_qi"],
		status_color(my["neili"], my["max_neili"]), my["neili"], my["max_neili"],
		my["jiali"] );

	if (ob->query("shen") >=0)
		printf(HIW"�� �� �� ��%8d              ", ob->query("shen"));
	else  
		printf(HIG"�� �� �� ��%8d              ", ob->query("shen"));
if (my["max_nuqi"] && my["nuqi"]>0)
    {
    if (my["nuqi"]>=my["max_nuqi"])
      {
       ob->set("nuqi",ob->query("max_nuqi"));
	     printf(HIR "�� �� " BLINK "ŭ"+NOR+HIR" �� ŭ������ \n"NOR);
      }
    else
      printf(HIR "�� �� ŭ �� %4d / %4d \n"NOR, my["nuqi"], my["max_nuqi"]);
    }
else 
	  printf(HIC "�� �� �� �� %s%4d / %4d \n"NOR,status_color(my["tili"], my["max_tili"]), my["tili"], my["max_tili"]);
	printf(HIW"�� ʳ �� �� %s%4d/ %4d      " HIW "     �� Ǳ �� ��  %s%d\n" NOR,
		status_color(my["food"], ob->max_food_capacity()),
		my["food"], ob->max_food_capacity(), HIY,
		(int)ob->query("potential") - (int)ob->query("learned_points"));
	printf(HIW"�� �� ˮ �� %s%4d/ %4d      " HIW "     �� �� �� ��  %s%d\n" NOR,
		status_color(my["water"], ob->max_water_capacity()),
		my["water"], ob->max_water_capacity(), HIM,
		my["combat_exp"] );
	printf(HIC"��"HIY"������������������������������������������������������������"HIC"��\n"NOR);
	
	if (flag) {
		printf("�����Ŀǰ�����ߡ�\n");
		destruct(ob);
	}
	return 1;
}
 
string status_color(int current, int max)
{
	int percent;
 
	if( max>0 ) percent = current * 100 / max;
	else percent = 100;
	if( percent > 100 ) return HIC;
	if( percent >= 90 ) return HIG;
	if( percent >= 60 ) return HIY;
	if( percent >= 30 ) return YEL;
	if( percent >= 10 ) return HIR;
	return RED;
}
 
int help(object me)
{
	write(@HELP
ָ���ʽ : hp
           hp <��������>                   (��ʦר��)
 
    ���ָ�������ʾ���ָ�����󣨺�����ľ�������Ѫ����
����������������ʳ���ˮ��Ǳ���Լ��������ֵ��
 
see also : score
HELP
	);
	return 1;
}