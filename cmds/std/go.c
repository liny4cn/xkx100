// go.c
inherit F_CLEAN_UP;

#include <ansi.h>


mapping default_dirs = ([
	"north":	"����",
	"south":	"�Ϸ�",
	"east":		"����",
	"west":		"����",
	"northup":	"����",
	"southup":	"�ϱ�",
	"eastup":	"����",
	"westup":	"����",
	"northdown":	"����",
	"southdown":	"�ϱ�",
	"eastdown":	"����",
	"westdown":	"����",
	"northeast":	"����",
	"northwest":	"����",
	"southeast":	"����",
	"southwest":	"����",
	"up":		"����",
	"down":		"����",
	"enter":	"����",
	"out":		"����",
	"in":		"��",
	"left":		"��",
	"right":	"��",
	"leitai":	"��̨����",
]);

string day_event() { return NATURE_D->outdoor_room_event();}
void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string dest, mout, min, dir, blk, gud, skill, face, thing_msg;
	object env, obj, blocker, thing, *f_obs, *ob;
	mixed horse;
	mapping exit;
	mixed oldobj;
	string riding;
	int result, i, my_dex, count = 0;

	if( !arg ) return notify_fail("��Ҫ���ĸ������ߣ�\n");
	if( me->over_encumbranced() )
		return notify_fail("��ĸ��ɹ��أ��������á�\n");
	if( me->query_temp("bixie/cizu") )
		return notify_fail("���˫�����ˣ��������á�\n");
	if( me->is_busy() )
		return notify_fail("��Ķ�����û����ɣ������ƶ���\n");
	if(strsrch(file_name(environment(me)), "/death/") < 0 &&
		me->is_ghost() && !wizardp(me))
		return notify_fail("���ǹ��꣬�������������ߡ�\n");

	env = environment(me);
	if(!env) return notify_fail("������Ҳȥ���ˡ�\n");

	if (me->is_fighting() )
	{
		f_obs = me->query_enemy();
		for(i=0; i<sizeof(f_obs); i++)
		{
//			if(f_obs[i]->query_temp("nian") == me)
			if(objectp(f_obs[i]) && environment(me) == environment(f_obs[i]))
			{
//			  if(f_obs[i]->query_temp("nian") == me->query("id"))	
			  if(f_obs[i]->query_temp("nian") == me)
		  	{	
			  	message_vision("$Nת��Ҫ�ߣ���$n̫������ճ��ճס����������п಻����\n", me, f_obs[i]);
			  	return notify_fail("���޷����ܡ�\n");
		  	}
			}
		}
		if (objectp(f_obs[0]) && !f_obs[0]->is_busy() )
			if (random((int)me->query("dex")) <= 
				random((int)f_obs[0]->query("dex")))
			{
				me->start_busy(1);
				message_vision("$N���Ʋ��ã�ת��Ҫ�ߣ���$nһ��������ǰ�����ߣ���û��ô���ף�\n", me, f_obs[0]);
				return notify_fail("������ʧ�ܡ�\n");
			}
	}

// ����������
//if( !env->valid_leave(me, arg) ) return 0;

	result = env->valid_leave(me, arg);
	if (!wizardp(me) || !me->query("env/invisibility"))
	{
		if ( result < 0 ) return 1;
		else if ( result == 0 )
		{
			if (query_fail_msg())
			{
				tell_object(me,query_fail_msg());
				return 1;
			}
			return 0;
		}
	}

	if( !mapp(exit = env->query("exits")) || undefinedp(exit[arg]) )
	{
		if( query_verb()=="go")
			return notify_fail("�������û�г�·��\n");
		else return 0;
	}
/*
	if(userp(me) && me->query("tili") <= 20)
	{
		message_vision(HIY"$N����ȫ����ʹ��ƣ�͸�����Ϯ����\n"NOR,me);
	}
	if(userp(me) && me->query("tili") <= 10)
	{
		message_vision(HIR"$N̫���ˣ�Ъ������߰ɡ�\n"NOR,me);
		return 1;
	}
	if(userp(me) && me->query("tili") <= 0)
	{
		message_vision(HIR"$NͻȻһ��ѣ�Σ��پ���������͸֧��\n"NOR,me);
		me->unconcious();
		return 1;
	}
*/
	if ( oldobj = me->query_temp("guardfor") )
	{
		if(objectp(oldobj))
		{
			if( !living(oldobj) || oldobj->query_temp("noliving") )
			{
				tell_object(me,"���������"+oldobj->name()+"��\n");
				me->delete_temp("guardfor");
			}
		}
	}

	dest = exit[ arg ];
	if ( !(obj = find_object(dest)) )
		call_other( dest, "???" );
	if ( !(obj = find_object(dest)) )
		return notify_fail( sprintf( "�޷��� %s �ƶ���\n", dest ) );
	if( obj->query("day_shop") && ( day_event() == "event_night" ||
		day_event() == "event_midnight"))
		return notify_fail(obj->query("short")+"���ϲ�������������������\n");
       
       if (  me->query_temp("LAST_PKER_TIME") && 
	     ( obj->query("no_fight")|| 
	     base_name(obj)=="/d/taohuacun/taohua1") &&
	     time() - me->query_temp("LAST_PKER_TIME")<7200 && !wizardp(me))
	     return notify_fail("ɱ���ˣ��ɲ�������ͷ�ڹ꣡\n");
	if ( horse = me->query_temp("is_riding"))
	{
		if (objectp(horse))	riding = horse->name();
		else if (stringp(horse))riding = horse;	
	}
	if ( stringp(riding) &&
		(arg=="up" || arg=="down" || arg=="leitai" ||
		arg=="enter" || arg=="out"))
		return notify_fail("�������û�����������Ϲ�ȥ��\n");

	ob = all_inventory(obj);
	for(i=0; i<sizeof(ob); i++)
		if( living(ob[i]) && !ob[i]->query_temp("noliving") &&
			ob[i] != me )
			count++;
// �ƶ�ǰ���Ƿ�̫��? ��̨�ϲ�����2��
	if ( arg == "leitai")
	{
		if (!wizardp(me) && count>2)
		return notify_fail("��̨����̫���ˣ�����ȥ�ұ�ȥ����\n");
	}
	else
	{
		my_dex = (int)me->query_dex();
		if (!wizardp(me) && userp(me) &&
			(((my_dex < 15) && (count > 15)) ||
			((my_dex < 20) && (count > 20)) ||
			((my_dex < 30) && (count > 30)) ||
			((my_dex < 40) && (count > 40)) ||
			(count > 50)))
			return notify_fail("ǰ����̫���ˣ�����ô��Ҳ������ȥ��\n");
	}
//	if( !env->valid_leave(me, arg) ) return 0;
//	if( userp(me)) me->add("tili", -1);

	if( !undefinedp(default_dirs[arg]) )
		dir = default_dirs[arg];
	else dir = arg;

	if( me->is_fighting() )
	{
		if( me->query("race") == "����" )
		{
			if (stringp(riding) )
			{
				mout = me->name()+"����" + riding + "������" + dir + "��Ķ����ˡ�\n";	       
				min = me->name()+"����" + riding + "����ײײ�����˹�����ģ����Щ�Ǳ���\n";
			}
			else
			{
				mout = me->name()+"��" + dir + "��Ķ����ˡ�\n";
				min = me->name()+"����ײײ�����˹�����ģ����Щ�Ǳ���\n";
			}
		}
		else {
			mout = me->name()+replace_string( me->query("fleeout_message"), "$d", dir );
			min  = me->name()+me->query("fleein_message");
		}
	} 
	else
	{
		if( wizardp(me) && me->query("env/invisibility") &&
			(wiz_level(me) >= wiz_level(env)))
		{
			mout = "";
			min = "";
		}
		else
		{
			if( me->query("race") == "����" && me->query("age")>15)
			{
				face="��";
				if (me->query("gender")=="Ů��")
				{
					if (me->query("per") >= 30)
						face ="���޾���" + face;
					if ((me->query("per") >= 28) &&
						(me->query("per") < 30))
						face= "��������" + face;
					if ((me->query("per") >= 26) &&
						(me->query("per") < 28))
						face= "��������" + face;
					if ((me->query("per") >= 24) &&
						(me->query("per") < 26))
						face= "��ɫ����" + face;
					if ((me->query("per") >= 21) &&
						(me->query("per") < 24))
						face= "��Ŀ毺�" + face;
					if (me->query("str") <= 16)
						face = "ͤͤ����" + face;
					if ((me->query("str") <= 20) &&
						(me->query("str") > 16))
						face= "��̬��ӯ"+ face;
					if ((me->query("per") < 21) &&
						(me->query("str") > 20) ||
						!userp(me))
						face = "";
				}
				else
				{
					if (me->query("per") >= 30)
						face= "�����ٷ��" + face;
					if ((me->query("per") >= 26) &&
						(me->query("per") < 30))
						face="Ӣ������" + face;
					if ((me->query("per") >= 22) &&
						(me->query("per") < 26))
						face="�Ǳ�����" + face;
					if (me->query("str") >=23)
						face = "����׳˶" + face;
					if ((me->query("str") >= 20) &&
						(me->query("str") < 23))
						face= "�����Բ"+ face;
					if ((me->query("per")<22) &&
						(me->query("str")<20) ||
						!userp(me))
						face = "";
				}
			} else face="";
			if (objectp(thing = me->query_temp("armor/cloth")))
				thing_msg = "����" + thing->query("name");
			else thing_msg = "ȫ���������";
			if (objectp(thing = me->query_temp("weapon")))
				thing_msg += "��ִ" + thing->query("name");
			if( me->query("race") == "����" )
			{
				if ( arg == "leitai")
				{
					mout = me->name()+"˫�����ţ��������Σ�����Ծ����̨��\n";
					min = me->name()+"����̨��һԾ�������ȵ�����̨�ϡ�\n";
				}
				else
					if( env->query("outdoors") && stringp(riding) )
					{
						mout = me->name()+"����"+riding+"��" + dir + "���۶�ȥ��\n";
						min = face + me->name() + thing_msg + "����"+riding+"һ·���۶�����\n";
					}
					else
					{
						mout = me->name() + "��" + dir + "�뿪��\n";
						min = face + me->name() + thing_msg + "���˹�����\n";
					}
			}
			else
			{
				mout = me->name()+replace_string( me->query("comeout_message"), "$d", dir );
				min = me->name()+me->query("comein_message");
			}
		}
	}
/* ��Ч�ػ� */
	if( strlen(env->query("guarded/"+arg)) < 3 )
		env->delete("guarded/"+arg);
	if( env->query("guarded/"+arg) )
		blocker = present(env->query("guarded/"+arg), env);
/* �˲����Զ�ʧȥ�ػ� */
	if(!blocker) env->delete("guarded/"+arg);
	if( env->query("guarded/"+arg) &&
		me->query("race") == "����" && blocker != me)
	{
		if(interactive(blocker) && living(blocker))
		{ /* �������ػ� */
			if( !stringp(riding)) /*����������*/
			{
				if(me->query_dex()<blocker->query_dex()+5+random(5))
				{
					message_vision("$N��ͼ��"+dir+"��ȥ�����Ǳ�$n��ס�˳�·��\n", me, blocker);
					return 1;
				}
				mout = me->name()+"ʩչ�Ṧ����" + blocker->name() +"����һ�ζ��������½�Ҳû���š�\n";
			}
			else /* �������� */
			{
				if( me->query("combat_exp") >=
					blocker->query("combat_exp"))
				{
/*
					if(blocker->query_temp("is_riding"))
					{
						message_vision(HIR"$N����"+rided_name+"�������һͷ��$n��������ײ������ˤ���Ľų��졣\n"NOR, me, blocker);
						blocker->query("rided")->delete("rider");
						blocker->delete("rided");
					}
					else message_vision(HIR"$N����"+rided_name+"���������$nײ���Ľų��졣\n"NOR, me, blocker);
*/
					message_vision(HIR"$N����"+riding+HIR"���������$nײ���Ľų��졣\n"NOR, me, blocker);
					blocker->receive_wound("qi",50);
					blocker->start_busy(2);
					blocker->delete_temp("guardto");
					env->delete("guarded/"+arg);
				} 
				if( me->query("combat_exp") <
					blocker->query("combat_exp")/2)
				{
					message_vision(HIG"$Nһ��ץס"+riding+HIG"����������$n���˴�����һ��ͣ��������\n"NOR,blocker,me);
					me->start_busy(2);
					blocker->start_busy(1);
					return 1;
				}
				else
					if( me->query("combat_exp") <
						blocker->query("combat_exp"))
						message_vision(RED"$N��$n����"+riding+RED"��������Ͻ�����һ����$nͨ����\n"NOR, blocker, me);
			}
		}
		else mout = me->name()+"����"+blocker->name()+"��"+dir+"���˳�ȥ��\n";
	}

	if(me->query_temp("guardto"))
	{
		env->delete("guarded/"+me->query_temp("guardto"));
		me->delete_temp("guardto");
		mout = me->name()+"�����ػ�����"+dir+"��ȥ��\n";
	}
	if (me->query_condition("baitan"))
	{
		"/cmds/std/baitan"->halt_baitan(me);
		me->clear_condition("baitan");
	}
	message( "vision", mout, environment(me), ({me}) );
	if( me->move(obj) )
	{
		me->remove_all_enemy();
		if (me->query_temp("pretend") && stringp(me->query_temp("apply/come_msg")))
		min = me->query_temp("apply/come_msg");
		message( "vision", min, environment(me), ({me}) );
		me->set_temp("pending", 0);
		if (me->query_temp("no_follow"))
		  me->delete_temp("no_follow");
		else 
		  all_inventory(env)->follow_me(me, arg);
		return 1;
	}

	return 0;
}

void do_flee(object me)
{
	mapping exits;
	string *directions;

	if( !environment(me) || !living(me) || me->query_temp("noliving"))
		return;
	exits = environment(me)->query("exits");
	if( !mapp(exits) || !sizeof(exits) ) return;
	directions = keys(exits);
	tell_object(me, "�������һ���������...\n");
	main(me, directions[random(sizeof(directions))]);
}

int help(object me)
{
	write(@HELP
ָ���ʽ : go <����>
 
    ���ָ��������ָ���ķ����ƶ�������ֱ�Ӽ��뷽�򣬿��ܴ��ڵķ�����
������������壩���������������������ϣ��������裨�󣩡�����
������裨������룺������򡢳�ȥ��������ȡ��ý���ָ�����
�궴����ݶѵȵȡ�

 
HELP
	);
	return 1;
}

