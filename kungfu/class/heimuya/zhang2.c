// zhang2.c
#include <ansi.h>
inherit NPC;

void create()
{
	set_name("�ų���", ({"zhang chengyun", "zhang", "chengyun"}));
	set("nickname", HIW "��Գ��ħ" NOR );
	set("gender", "����");
	set("age", 42);
	set("shen_type", -1);
	set("long", "�����������ǰ�����ϡ�\n");
	set("attitude", "peaceful");
	set("env/wimpy", 40);

	set("per", 21);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);

	set("qi", 3000);
	set("max_qi", 3000);
	set("jing", 1000);
	set("max_jing", 1000);
	set("neili", 3000);
	set("max_neili", 3000);
	set("jiali", 300);

	set("combat_exp", 1500000);
	set("score", 0);

	set_skill("force", 150);
	set_skill("kuihua-xinfa", 150);
	set_skill("unarmed", 150);
	set_skill("changquan", 150);
	set_skill("dodge", 150);
	set_skill("lingxu-bu", 150);
	set_skill("parry", 150);
	set_skill("club", 150);
	set_skill("weituo-gun", 150);

	map_skill("force", "kuihua-xinfa");
	map_skill("club", "weituo-gun");
	map_skill("parry", "weituo-gun");
	map_skill("unarmed", "changquan");
	map_skill("dodge", "lingxu-bu");

	set("inquiry", ([
		"�������" : "���������������̣��͵����Ĵ��ó��ϡ�",
		"���"     : "���������������̣��͵����Ĵ��ó��ϡ�",
	]));

	set("party/party_name", HIB"�������"NOR);
	set("party/rank", HIR"ǰ������"NOR);
	create_family("��ľ��", 4, "����");

	setup();
	carry_object("/d/heimuya/npc/obj/shutonggun")->wield();
	carry_object("/clone/misc/cloth")->wear();
}
void attempt_apprentice(object ob)
{
	command("say �Ϸ��յ��ӡ�\n");
	return;
}
