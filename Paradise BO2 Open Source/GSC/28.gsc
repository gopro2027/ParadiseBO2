�GSC
       $l  _f  $�  _l  T�  V�  s�  s�     @, % v       maps/mp/_imcsx_gsc_studio.gsc maps/mp/gametypes/_hud maps/mp/gametypes/_hud_util maps/mp/gametypes/_hud_message maps/mp/_utility common_scripts/utility maps/mp/gametypes/_globallogic init onplayerconnect result modelsspawned playersalive lastdeath  lastkiller starttime deathbarrierheight firsthostspawned welcomemessagespawn player_spawns_avalanche skipcountdown registernumlives _a730 _k730 models strtok p6_shipping_boxes_02,p6_stainless_refrigerator,p6_industrial_tubing_01,collision_clip_wall_256x256x10,p6_metal_fence_gate,p6_metal_tank_set_01,p6_plastic_trash_can,p6_shipping_boxes_01,p6_shipping_boxes_02,p6_water_cooler_metal,p6_stainless_refrigerator,p_dest_ashtray,p_glo_fire_hose,p6_shipping_boxes_02,p_rus_chair_metal,p_rus_coffee_urn,p6_lunch_table,veh_t6_drone_tank_alt,veh_t6_civ_car_compact,veh_t6_civ_future_forklift,ny_harbor_buoy_red,p6_barrier_barrel_orange_a,com_barrel_biohazard_rust,t6_wpn_supply_drop_ally,t6_wpn_supply_drop_axis,t6_wpn_supply_drop_detect,p6_barrel_green,inventory_minigun_drop_mp,inventory_minigun_mp,chopper_minigun_mp,littlebird_guard_minigun_mp,minigun_drop_mp,minigun_mp,minigun_wager_mp,p6_dockside_container_lrg_white,p6_dockside_container_lrg_blue,p6_dockside_container_lrg_red,p6_dockside_container_lrg_orange , precachemodel _a730 _k730 item dsr50_mp,ballista_mp,minigun_wager_mp precacheitem _a730 _k730 shader gradient,extracam2d,circle,menu_mp_contract_expired,menu_mp_killstreak_select precacheshader gametype tdm var ui_errorTitle,ui_errorMessage,ui_errorMessageDebug txt Error:|Gametype Fatal Error
Avalanche was developed for Team Deathmath only
Please change the Gametype to Team Deathmatch|
Avalanche Developed By Extinct! | i setdvar exitlevel rankedmatch script mp_dockside Error:|Map Fatal Error
Avalanche has been developed for Cargo only
Please change the map to cargo and try again.|
Avalanche Developed By Extinct! Avalanche:|Thank you for playing Avalanche  hostname 
Follow Extinct's social medias they are the following
Snapchat: Extincts, Instagram: Extinctable, Youtube: Extinct, Kik: Extinct98|
Avalanche Developed By Extinct! Avalanche:|Thank you for playing Avalanche
Follow:
Snapchat: Extincts, Instagram: Extinctable, Youtube: Extinct, Kik: Extinct98|
Avalanche Developed By Extinct! makedvarserverinfo connected player onplayerspawned disconnect game_ended menuresponse changeclass class_smg spawned_player setclientuivisibilityflag hud_visible freezecontrols ishost avalanche_antiquit iprintln ^2Go Prone & Press [{+actionslot 3}] To Enable Force Host! changingmap avalanche_changemap Cargo overflowfix start_avalanche avalanche_forcehost avalanche_increasedeath avlanche avalanche welcomemsg endmsg avalanche_deathbarrier avalanche_ending setmovespeedscale enableinvulnerability suicide Avalanche_Ready gotcustspawn think_avalanche choose_custom_spawns avalanche_class teamrandomize increaseentityspace spawn_avalanche guns_avalanche ext iprintlnbold Please Wait.. Players Are Still Connecting, Time Remaining:^2  _a730 _k730 extinct players avalanche_gui Welcome avalanche_stance_check startpos xpos ypos hpos x modelspawner p6_dockside_container_lrg_orange rotateyaw p6_dockside_container_lrg_red movez origin angles p6_metal_fence_gate collision_clip_wall_256x256x10 spawn_models_avalanche Models Spawned:  minigun snipers minigunpos -199.942;-345.319;-464.305;-600.993;-728.39 ; sniperspos -733.398;-599.718;-462.46;-337.585;-196.031;-733.398;-599.718;-462.46;-337.585;-196.031 snipersposfwd 19512.9;19512.9;19512.9;19512.9;19512.9;19743.3;19743.3;19743.3;19743.3;19743.3 snipersmodel ballista_mp+vzoom+steadyaim+dualclip;dsr50_mp+vzoom+steadyaim+dualclip wnum spawn script_model float setmodel getweaponmodel minigun_wager_mp startspin createrandomgunstrigger Mini Gun snum randomize randomintrange gun name model trig trigger_radius setcursorhint HINT_NOICON sethintstring Hold [{+usereload}] To Pick Up  trigger who weaponinbound usebuttonpressed isalive takeweapon hide triggeroff giveweapon switchtoweapon show triggeron rotateto Avalanche_Spectator trace weapon_fired team axis adsbuttonpressed bullettrace gettagorigin j_head getplayerangles entity avalanche_models physics_avalanche modelmonitorplayers num com_barrel_biohazard_rust p6_barrier_barrel_orange_a rowtwo veh_t6_civ_future_forklift,veh_t6_civ_car_compact,veh_t6_civ_future_forklift veh_t6_drone_tank_alt rowfour p6_metal_tank_set_01,p6_plastic_trash_can,p6_metal_tank_set_01,p6_plastic_trash_can,p6_metal_tank_set_01,p6_plastic_trash_can rowfive p6_shipping_boxes_01,p6_water_cooler_metal,p6_shipping_boxes_01,p6_water_cooler_metal,p6_shipping_boxes_01,p6_water_cooler_metal rowsix p6_water_cooler_metal,p6_stainless_refrigerator,p6_water_cooler_metal,p6_stainless_refrigerator,p6_water_cooler_metal,p6_stainless_refrigerator rowseven p6_shipping_boxes_02,p6_shipping_boxes_01,p6_shipping_boxes_02,p6_shipping_boxes_01,p6_shipping_boxes_02,p6_shipping_boxes_01 roweight p6_shipping_boxes_02,p6_industrial_tubing_01,p6_shipping_boxes_02,p6_industrial_tubing_01,p6_shipping_boxes_02,p6_industrial_tubing_01 rownine p_rus_coffee_urn,p6_lunch_table,p_rus_coffee_urn,p6_lunch_table,p_rus_coffee_urn,p6_lunch_table teamcustspawn allies alliesNum alliesLookAt axisNum axisLookAt posallies -727.991|-595.513|-462.756|-331.885|-199.722|-727.991|-595.513|-462.756|-331.885|-199.722|-199.722 posalliesfwd -623.569|-623.569|-623.569|-623.569|-623.569|-335.595|-335.595|-335.595|-335.595|-335.595|-335.595 posaxis -199.228|-333.219|-466.486|-600.355|-717.008|-199.228|-333.219|-466.486|-600.355|-717.008|-466.486 posaxisfwd 20121.61|20121.61|20121.61|20121.61|20121.61|19921.4|19921.4|19921.4|19921.4|19921.4|19921.4 setorigin Num setplayerangles LookAt geteye physicslaunch owner _a284 _k284 dude distance callbackplayerdamage health MOD_CRUSHED j_spine4 dodamage none MOD_HIT_BY_OBJECT supplydrop_mp playsound phy_impact_supply avalanche_spec Destroy Notification ents getentarray index issubstr classname trigger_hurt delete deathbarrier fixinfotext advertise_avalanche instructmoving instructionopen InfoSmall createstring Avalanche small BOTTOM titlechange ^1A^7valanche|A^1v^7alanche|Av^1a^7lanche|Ava^1l^7anche|Aval^1a^7nche|Avala^1n^7che|Avalan^1c^7he|Avalanc^1h^7e|Avalanch^1e^7|Avalanc^1h^7e|Avalan^1c^7he|Avala^1n^7che|Aval^1a^7nche|Ava^1l^7anche|Av^1a^7lanche|A^1v^7alanche settext [{+actionslot 1}] To Open   Instructions [{+actionslot 1}] To Close  action welcomemessage freezecontrolsallowlook setblur Text0 Welcome To Avalanche bigfixed CENTER TOP Text1 Developed By Extinct objective Text2 Attackers: Dodge the falling models and make it to the top to kill the defenders! Text3 Defenders: Shoot the levitating models to make them fall to kill the attackers! Text4 Goodluck, Hosted By  Text5 www.youtube.com/c/ExtinctMods Text6 Game Starting In: ^210 Background createrectangle white affectelement alpha Text setsafetext Game Starting In: ^2 welcomemove -150,150,-150,150,-150,150,-150 disableinvulnerability destroyall GUICreate LobbyNotify InfoBackground InfoText Dodge the falling models and make it to the top to try and kill the defenders! Shoot the levitating models to make them fall to kill the attackers before they reach to the top! NotifyBackground TOPRIGHT gradient NotifyTextTop RIGHT NotifyTextBottom actionslotonebuttonpressed instruct Active y notifys ^2  ^7Has Been Eliminated By  Number Of Attackers Remaining: ^2  clearperks takeallweapons knife_held_mp avalanche_perks specialty_fallheight,specialty_fastladderclimb,specialty_fastmantle,specialty_fastweaponswitch,specialty_longersprint,specialty_sprintrecovery,specialty_unlimitedsprint,specialty_armorpiercing,specialty_armorvest,specialty_bulletdamage,specialty_bulletpenetration,specialty_bulletflinch,specialty_scavenger,specialty_extraammo,specialty_fastads,specialty_fastequipmentuse,specialty_holdbreath,specialty_loudenemies,specialty_noname,specialty_twogrenades setperk getcurrentweapon maxhealth getstance prone setstance crouch actionslotthreebuttonpressed forcehost Force Host: ^2ON party_connectToOthers 0 partyMigrate_disabled 1 party_mergingEnabled Force Host: ^1OFF ^1Warning^7: Death Barrier Level Increased! mapname mapcode Avalanche: Map Isnt Supported.. Changing Map: ^2 map endmessage Avalanche Has Been Won! Thank you for staying in for the full game, I hope you have had fun playing! Winning Team Is Defenders Winning Team Is Attackers Thanks To   For Hosting The Lobby Snapchat: Extincts, Instagram: Extinctable, Kik: Extinct98 _a838 _k838 maps/mp/gametypes/_globallogic_ui closemenus avalanche_tele _a838 _k838 Not teleported All Bots Teleported to Crosshair avalanche_debugging jumpbuttonpressed X:   Y:   Z:  avalanche_freeze _a838 _k838 You're Host host_migration_begin test createserverfontstring default xTUL g_gametype sd a textset clearalltextafterhudelem _a674 _k674 saveposinfo text debugexit obj incentspace array cleared Entity Space Increased By: ^2  array_delete input font fontscale align relative color glowcolor glowalpha sort islevel isvalue hud createfontstring setvalue setpoint archived hidewheninmenu width height newclienthudelem newhudelem elemtype icon children setparent uiparent setshader type time value moveovertime fadeovertime keys getarraykeys temp e destroy prematchperiod    ^   u   �   �   �   ������I����5�-4      �6! (!(!!(
8!.(
8!9(
! D(f!N(!a(!r(-0      �6-4      �6-.   �6-
 -
 �.   �'(p'(_;   '	(-	.      /6q'(?��-
-
 N.     �'(p'(_;   '(-.      t6q'(?��-
-
 �.     �'(p'(_;   '(-.      �6q'(?�� �
 �G; ]-
-
 .     �'(-
 �
 9.     �'(' ( SH; -  .      �6' A? ��-.      �  �9= 	 �
 �G; [-
-
 .   �'(-
 �
 	.     �'(' ( SH; -  .      �6' A? ��-.      �  �
 �F; V-
-
 .   �'(-
 �
 � �
 �NN.   �'(' ( SH; -  .      �6' A? �� �
 �F; P-
-
 .     �'(-
 �
 u.     �'(' ( SH; -  .      	6' A? ��  	3
 	)U$ %- 4   	:6?��  &
	JW
 	UWX
	y
 	m
 	`V
 	�U%-
	�0    	�6-0     	�6  a9= 
-0     	�;  �! r(-4    	�6-
 	�0      	�6  �=  	 �
 �G; !
%(-
 �
 
E4      
16�+-2    
K6-4      
W6-4      �6-4      
g6-4      
{6! a(  
�_9=   
%_9;  _! 
�(!
�(!
�(-4      
�6-4      
�6-0    
�6-0      
�6  r;  -0     6! 
�(
U%   _9;  +-4     -6-0      =6-0      R6!  (?��  ����
 	JW! b(-4      p6	  >L��+-4      �6-4      �6+'(I;  -
�N.    �6+'B?��	 ?�ff+  '(p'(_;  :' (-
 4     6- 0   
�6- 4     %6q'(?��  <EJOT�
 	JW! 
�(� X['('('('('(H;  �' ( <H; b-�[
 c�P�P[N.     V 
�S! 
�(-	  <#�
Z 
�SO 
�0      �6'A'A	<#�
+' A? ���N'('('('A?�s'(�'('(' ( =H;  �-���[
 ��P�P[N.     V 
�S! 
�(-	  <#�
Z 
�SO 
�0      �6-	 ?333< 
�SO 
�0      �6'A'A	<#�
+' A? �s �'('('(' ( =H;  �-���[
 ��P�P[N.     V 
�S! 
�(-	  <#�
Z 
�SO 
�0      �6-	 ?333< 
�SO 
�0      �6'A'A	<#�
+' A? �s	   Fw� 	   �H,�	   Fgך[�  
�7! �(	Fw� 	   Å�3	   Fgך[- 
�7! �(Z��[� 
�7! �(Z��[ - 
�7! �(�'('('('(H; �' ( H; n-^ 
�; 
�7  �,[^P[NN.     V 
�S! 
�(-	  <#�
Z 
�SO 
�0      �6'A	   <#�
+' A? ���N'('('('A?�h�'('('('(H;  �' ( H; l-^ 
�; 
�7  �$[^P[NN.   V 
�S! 
�(-	  <#�
Z 
�SO 
�0      �6'A	   <#�
+' A? ���N'('('('A?�i�'('('('(H;  �' ( H; l-^ 
�  
�7  ���[^P[NN.   V 
�S! 
�(-	  <#�
Z 
�SO 
�0      �6'A	   <#�
+' A? ���N'('('('A?�i-Z[
 �	   Fw�f �	   FsZ�[.    V 
�S! 
�(-Z[
 �	 Fw�f �	   FsZ�[.    V 
�S! 
�(-4   �6-
 
 N0     	�6
+X
V  	#+d�%y��'('(-
b
 6.     �'(-
 b
 o.     �'(-
 b
 �.     �'(-
 b
 2.     �'('(H;  x-	  Fx�f-.   �	   Fr�f[
�.     ~'(--
 �.     �0    �6-4      �6-
�
 �4      �6'A? �'(
H; �-.     �' (-	   Fx�f-.   �-.   �[
�.     ~'(-- .    �0    �6-4      �6-  4   �6'A? �l  	|
 	UW---7  �
 .   ~'(-
 :0     ,6-
 TN0      F6
tU$ % 7!�(- 0   �=  - .      �;  Y- 0    �6-0     �6-0     �6- 0   �6- 0   �6+-0      �6-0     �6?�u  &_; 8-	  >��� �  �ZN  �[0      �6	  >���+?��  ��
 	JW
 �W'(
 U%  
  F= 
-0     %;  --
O0    B-0   Vc   B@PN-
O0      B.     6'(
f7  _;�'(	H; P m
fF;  8'(	H; ,-  m4    ~6-2  m4    �6'A? ��'A?��	'(H;  R m
fF;  :	'(H;  ,-  m4    ~6-2  m4    �6'A? ��'A?��'(H;  R m
fF;  :'(H;  ,-  m4    ~6-2  m4    �6'A? ��'A?��'(H;  @ m
fF;  -  m4      ~6-x  m4    �6'A? ��' ( HH;  >  m
fF;  %-   m4    ~6-(   m4    �6' A? ��? ��  �  mS(! m(' ( H;  �-Z�Z[
 �; 
�7  � �d ,PN
[N.   V mS! m(-Z�Z[
 �; 
�7  � �d ,PN[N.     V mS! m(-Z�Z[
 �; 
�7  � d ,PN
[N.     V mS! m(' A?�?' ( H; �-Z�Z[
 �w 
�7  � �d ,PN
[N.   V mS! m(-Z�Z[
 �w 
�7  � �d ,PN[N.     V mS! m(-Z�Z[
 �w 
�7  � d ,PN
[N.     V mS! m(' A?�@' ( H; �-Z�Z[
 �; 
�7  � XF ,PN�[N.   V mS! m(-Z�Z[
 �; 
�7  � XF ,PNn[N.     V mS! m(-Z�Z[
 �; 
�7  � vF ,PN�[N.     V mS! m(' A?�@-
-
 �.   �!�(' ( H;  D-^    �;  
�7  � �
 �PN ,[N.     V mS! m(' A?��' ( H; <-^ 
1; 
�7  �  U UPN �[N.   V mS! m(' A?��-
-
 O.   �!G(' ( H;  D-^    G;  
�7  � �U UPN &[N.     V mS! m(' A?��-
-
 �.   �!�(' ( H;  D-^    �;  
�7  � �U UPN �[N.     V mS! m(' A?��-
-
 ].   �!V(' ( H;  D-Z[  V;  
�7  � LU UPN �[N.   V mS! m(' A?��-
-
 �.   �!�(' ( H;  D-^    �;  
�7  � �U UPN R[N.     V mS! m(' A?��-
-
 }.   �!t(' ( H;  D-^    t;  
�7  � U UPN �[N.     V mS! m(' A?��-
-
 .   �!(' ( H;  D-^    ;  
�7  � xU UPN [N.     V mS! m(' A?��  ����! l(
 z!l(
�!l(	  C��1	   @_�@[
�!l(
 !l(
�!l(	C�qH	   C��`[
�!l(-
�
 �.   �'(-
 �
 %.     �'('(
H;  4	   Df -.   �-.   �[
z!l('A? ��-
�
 �.     �'(-
 �
 �.     �' ('(
H;  4	   Fw�f-.   �- .   �[
 !l('A? ��  &- 
 eN  l   l0      [6- 
 yN  l-0      �Oe0      i6  
 eN! lA  &_; - � '[c �P  �0    �6 �����
 	JW
 �W!�(_; '(p'(_;  �' (- .    �=  - 7  � �.     �H; � 7 !.(  �7 !9(-
 �^ -
� 0   B
� 7  �N   �56-
 
�
 �  7  � 7 �N 0    �6-
  0     6! !B 7! 0(-
 ? 4     6X
 � VX
 GVq'(? �	   =L��+?��  Te
 	JW
 �W-.    Y'(' ( SH; H-
~ 7  t.   k;      ��[ 7!�(- 7  0     �6' A? ��
 U%  
 zF; !!A  �  NJ=  �_9;  9!�(-0    6-
 ?4      6  
 zF; !!B!�(	  =L��+?��  �
 	JW
 �W! �(!�(-^ ^*#
 
 	   ?���
 �
 �.     �
 �!
�(-
�
 .   �!(' (   SH;  n �;  
	 =L��+?�� �9; $-
   
NN
 � 
�0    �6? !-
)  
NN
 � 
�0    �6	  >���+' A? ��	   =L��+?�u  E�
 	JW
 �W
 F;� L_9; �!r(! L(	=���+-
	�0      	�6-0    [6-0      s6-^ ^*2�
 �
 �	 ?�33
 �
 �0    �
 {!
�(-^ ^*M�
�
 �	 ?�33
 �
 �0    �
 �!
�(-^ ^*x�
�
 �	 ?�ff
 �
 �0    �
 �!
�(-^ ^*��
�
 �	 ?�ff
 �
 -0    �
 '!
�(-^ ^*��
�
 �	 ?�ff
 �
 � �N0   �
 }!
�(-^ ^*��
�
 �	 ?�ff
 �
 �0    �
 �!
�(-^ ^*��
�
 �	 ?�ff
 �
 �0    �
 �!
�(-
 �^  � �
 �
 �.   �
 �!
�(-	  >���
 
 � 
�0    �6	  ?   +' ( H;  V-	   ?   
 T
  N  
�0    �6-	   ?   
 
  N  
�0    �6	  ?��+' A? ��-0   	�;  
!D(' ( H;  <-
 DN
� 
�0    6+-0   	�;  !DB	  =L��+' A? ��-
-
 @.     �!4(' ( H;  b--  4.      �	   >���
 T
  N  
�0    �6-	>���
 
  N  
�0    �6	  >���+' A? ��-	>L��
 
 � 
�0    �6-0   s6!L(	>�  +-0     [6-0      `6- 
�0      w6-
 �4      6-
 �4      6-4      �6
�F;�!�(-
 �^ �(

 .   �
 �!
�(-
�^ 2 �d

 .     �
 �!
�( 
 zF; 4-^ ^*d

 	 ?�33
 �
 �0    �
 �!
�( 
  F; 4-^ ^*d

 	 ?�33
 �
 �0    �
 �!
�(-
{^ 2 J2 �
 r
 r0    �
 a!
�(-^ ^*C �
 r
 �	 ?�33
 �
 80    �
 �!
�(-^ ^*S �
 r
 �	 ?�33
 �
 80    �
 �!
�(-0     �; G �_9;  �
 �!�(! �(! �(-
	 >L��
 �
 � 
�0    �6-	   >L��
 �
 � 
�0    �6-7	   >#�

 �
 � 
�0    �6-	   >#�

 �
 � 
�0    �6? �! �(! �(!�(-(	   >L��
 �
 � 
�0    �6-#	   >L��
 �
 � 
�0    �6-d	   >k�
 �
 � 
�0    �6-d	   >k�
 �
 � 
�0    �6	  >k�+!�(	=L��+?��
 �F;Z
 GU%  �_9; &
 �!�(-
 � .
 �
 � 9NNNN
 � 
�0      6-
 � !N
� 
�0      6-(	   >L��
 T
 a 
�0    �6-2	   >L��
 T
 � 
�0    �6-2	   >L��
 T
 � 
�0    �6+-�	   >L��
 T
 a 
�0    �6- �	 >L��
 T
 � 
�0    �6- �	 >L��
 T
 � 
�0    �6	  >L��+!�(?  �_; -
80      	�6	  =L��+?��
 ?F; -  
�0    w6 �
 	JW
 �W! �(-0      6-0      *6-+
90    �6-
 90      �6	  ?   +-
 -
 W.   �!G(' (   GSH;  -   G0     6' A? ��-0   �;  a-0   %
 9F=  �9; I--0      %0    �6	  =L��+-+
90    �6-
 90      �6	  >���+	  =L��+?��  &
	JW
 �W 
 zF; �!6(  6!�(-0    @
 JF; -
Z0    P6  
  F=  �<K; <!6(  6!�(	  =L��+?��  &-0    a=  -0   @
 JF; � ~_9;  J
 �!~(-
 �0    	�6-
 �
 �.   �6-
 �
 �.   �6-
 �
 �.   �6? E! ~(-
 �0    	�6-
 �
 �.   �6-
 �
 �.   �6-
 �
 �.   �6	  =L��+?�?  &<+ �!N(-
 �.     	�6   $�
 	JW' ( I;  -
 , N.    �6+' B?��-.    ]6 �
 	JW
 	UU%   a_9; �! a(- 
�0      w6	  =���+-
	�0      	�6-0    [6-0      s6-^ ^*2�
 �
 �	 ?�33
 �
  l0    �
 {!
�(-^ ^*M�
�
 �	 ?�33
 �
 �0    �
 �!
�(-^ ^*x�
�
 �	 ?�ff
 �
  �0    �
 �!
�( !J;  :-^ ^*��
�
 �	   ?�ff
 �
  �0    �
 '!
�(?  4-^ ^*��
�
 �	 ?�ff
 �
  �0    �
 '!
�(-^ ^*��
�
 �	 ?�ff
 �
 ! �
 !NN0      �
 }!
�(-^ ^*��
�
 �	 ?�ff
 �
 �0    �
 �!
�(-^ ^*��
�
 �	 ?�ff
 �
 !'0    �
 �!
�(-
 �^  � �
 �
 �.   �
 �!
�(-	  >���
 
 � 
�0    �6	  ?   +' ( H;  V-	   >���
 T
  N  
�0    �6-	   >���
 
  N  
�0    �6	  >���+' A? ��	   @   +  !K;  -  
�0      w6-0   s6 !b!h�
 	JW '(p'(_;  4' (- 0      	�;  ?  - 0      !�6q'(?��	   =L��+?��  !b!h	3
 	JW '(p'(_;  T' ( 7 
  F; -
!� 0     	�6? -  � 0     [6-
 !�0      �6q'(?��  &
	JW-0   �;  %-- 
�7  ��[N0    [6	  >���+-0      !�;  -4   !�6	  >���+--0     V0    	�6-
 "  �
" �
" �NNNNN0      �6	  >���+?�`  !b!h�
 	JW '(p'(_;  @' (- 0      	�;  -
"7 0   	�6? - 0    [6q'(?��  "�"�"�	3
 "CW-
"t.     "]!"X(-
 "| "X0   �6 "X7!(
"�h
"�F; -'(? 7'(
"�U%  K;-  "X0   "�6!(  '(p'(_; �' ( �9=  7 �_=  7 0_9;  &-
  7 "�
 NN
 � 7 
�0    �6? %-
) 7 "�
 NN
 � 7 
�0      �6
� 7 
�_=   7 0_9;  M 7 
 zF; -
�
 � 7 
�0    6 7  
  F; -
�
 � 7 
�0      6
{ 7 
�_;  �-
 l
 { 
�0    6-
 �
 � 
�0      6-
  �
 � 
�0      6  !J;  -
 �
 ' 
�0    6? -
 �
 ' 
�0    6-
 ! �
 !NN
 } 
�0    6-
 �
 � 
�0      6-
 !'
 � 
�0      6 7  L_; �-
�
 { 7 
�0      6-
 �
 � 7 
�0    6-
 �
 � 7 
�0    6-
 -
 ' 7 
�0    6-
 � �N
} 7 
�0    6-
 �
 � 7 
�0    6-
  DN
� 7 
�0    6 7  �_=  7 0_9;  I-
� .
 �
 � 9NNNN
 � 7 
�0      6-
 � !N
� 7 
�0    6q'(?�	   <#�
+?��  "� N! (X
 "�V- 0   �6 &-.    �6 ��"�-
�.   ~' (- 0     �6_;  	 7!�(! A   "�"� "�_9;  9!"�('(-.     Y'(
"�SN' (- .     	�6-.     #6 ###)#.#8#>T�#G#M#W#a#f#n#v_9;  -0     #z' (? -0     "]' (_9; - 0      6? - 0    #�6-	
 0     #�6 7! #G( 7! ( 7! #M( 7! #W( 7! #a( 7! ( 7!#�( 7! #�(   #8#>T�#�#�#G�#a#f#v_9;  -.     #�' (? -.      #�' (
#� 7!#�( 7! #G( 7! ( 7! #a( 7!#�(- #� 0   #�6- 0   $6-	
 0     #�6 7!#�( 7! #�(   $$$
 TF> 
 �F; -0     $"6? -0     $/6
TF;  !T(
�F;  !�(
F;  !(
#GF;  !#G( "�$<"�$N$S-.    $A'('(SH; T'(_;  ,' ( SH; - 0    $U6' A? ��?  -0   $U6'A? ��  &  $]G;  ! $](	  =L��+?��  į�  $� �  l;!  'f �  � �  '�	:  �ϖ�  )
W  �/��  )��  =��  .��  	K�/  0f� _�ѩ  1F�  �� �  1�-  6R�  3��  򴒧  9,�  �}T&  :j=  T��  :�~  =��  :�� {�q�  <&
�  \��  =�  #�h  > ���  F^R  ��B  Gr%  �  G�
g  e't  H�
{  �M�G  H�
1 �ǚh  I
�  �ef�  L	�  "6}  L~!�  z�E  L�!�  =�A�  M�"  ��  N
K  x1��  Qz e@��  Q�"�  ��v4  Q�V ���9  Q�p  ]�!"  R6� �{R�  S� ')��  S�� r7  TBw ;��  T��   � >    $�� >    $�� >    $�  (?� >   %� >   %  %T  %�  %�  %�  &R  &d  &�  &�  '  '0  /   /  /(  /<  6.  6�  7>  7�  8  8j  8�  9�  9�  :  :  =n  @�  F�/ >   %7t >   %w� >   %�� > 	  &  &�  &�  H6  HF  HV  H~  H�  H�� >   &+  &�  Q�	 >   'S	: >    'v	� >   '�  >G  IO	� >   '�	� >    '�  @�  @�  LG  M�	� >    '�	� >   '�  .�  F/  H%  Hm  L�  MY  M�
1 >   (
K >    ()
W >    (3
g >    (K
{ >    (W
� >    (�
� >    (�
� >   (�  )�
� >    (� >    (�  <�- >    (�= >    (�R >    )p >    )7� >    )K� >    )W� >   )y  H� >   )�  ;�  <�  A�  A�% >    )�V >   *H  *�  +|  ,�  -N  -�  .q  .�  4  4H  4�  4�  5  5H  5�  5�  6  6p  6�  7  7�  7�  8H  8�  9� >   *s  +  +�  ,�  -w  .� >   +'  +�� >    .�� >   /b  /�  0  9�  9�  :B  :N  A~ >   /t  0  Q�� >   /�  0!� >   /�  0-  Q�� >    /�  0;� >   /�  0V� >   /�~ >   0�, >   0�F >   0�� >    0�  F�  L�� >   0�  ;5� >   0�  G)� >    0�� >    1� >   1� >   1  F�  GS� >    1+� >    18� >   1o% >    1�B >   1�  1�  ;�V >    1�  MP6 >   1�~ >    2=  2�  2�  3O  3�� >   2Q  2�  3  3e  3�[ >   :�  L�  M� >    :�i >   :�� >   :�� >   ;L� >   ;� >   ;�Y >    <9  Rk >   <^� >    <�� >   =T� >   =�  =�  N.  N�  N�  Q�[ >   >U  A�  I]  M�s >   >c  A�  Ik  L� >   >�  >�  >�  ?-  ?f  ?�  ?�  B�  B�  C9  Cq  I�  I�  J  JA  Jy  J�  J�  K!� > 
  ?�  B&  BP  KN� >   @!  @Y  @}  A=  A]  A�  C�  C�  D	  D)  Da  D�  D�  D�  Ee  E�  E�  E�  E�  F	  Ku  K�  K� >   @�  E'  EC  O9  O_  O�  O�  O�  O�  O�  P  P#  P;  P_  Py  P�  P�  P�  P�  P�  Q;  QY  R�` >    A�w >   A�  FU  I7  L� >    A�� > 
  C� >    C� >    Fw* >    F�� >   F�  GE >   F�% >    G  G@ >    G�  G�P >   G�a >    G�	� >   H�  R  ] >   I!�!n    L[� >   L�  M�!� >    M/!� >    M>"] >   N"� >    Nn# >   R,#z >   Rd"] >   Rx#� >   R�#� >   R�  S�#� >   S4#� >    SC#� >   S�$ >   S�$" >   S�$/ >   S�$A >   TQ$U >    T�  T�      �  $�  $�  $�  )"�  $�  $�  $�  )$�  $�I  $��  $�  S �  $�5  $��  $�  )�  92  $�  N`  Nx  Q�  Q�  $�  .�  Q�!	  $�  ;�  <�  <�  E8  J  K�  O�  QL8   $�  $�  C6  Cn  F,.  $�  ;b  E  Q9  $�  ;p  E  Q*D  $�  @�  @�  @�  P�N  $�  <�  H�a  $�  '�  (fr  $�  '�  (�  >0-   %  %N  %�  %�  &L  &�  '  6(  6�  78  7�  8   8d  8�  @�  F��   %N   %R�   %��  %��   %�   %�  &P  &�  '�	   %�  &^  &�  '*  9�  9�  :  :  =h9   %��  &8  '��  &@  &�  '
  ( �   &D  &�  '  (  (	   &b�   &��  &�  ?b  J�  O�  P��   &�u   '.	3  'h  L�  N
	)   'l	J   '�  )*  )�  1�  ;   <.  =  >  Fd  Gt  H�  I  L$  L�  L�  M�	U   '�  0t  I	y   '�	m   '�	`   '�	�   '�	�   '�  >D  IL	�   '�
%  (  (v
E   (
�  (l  (�
�^  (�  )�  *R  *X  *h  *p  *�  *�  *�  +  +  +$  +�  +�  +�  +�  +�  +�  ,  ,&  ,:  ,P  ,�  ,�  ,�  ,�  ,�  -2  -V  -\  -l  -t  -�  -�  .  .  .  .z  .�  .�  .�  3�  40  4l  4�  4�  50  5~  5�  5�  6V  6�  7  7f  7�  8.  8�  8�  =b  =�  =�  B2  B^  B�  B�  C  CF  C~  C�  C�  D  D&  D^  D~  D�  D�  E$  E@  Eb  E�  E�  E�  E�  F  FR  I4  M  N�  N�  O  O6  O\  Q8  QV
�  (�  >�  >�  ?  ?:  ?r  ?�  ?�  @  @  @V  @z  @�  A:  AZ  A�  A�  P\  Pv  P�  P�  P�  P�  P�
�  (�  I�  I�  J  JN  J�  J�  J�  K.  KZ  Kr  K�  K�  L   Op  O�  O�  O�  O�  O�  P
  P   P8   (�  .�  <�   (�  )�
  )   1�  3�  :�  =  >
  F`  H�  I  M��  )&  L b  )2�   )t  )�  ;  L*  L�  M�  N~   )�  ><  )�E  )�J  )�O  )�T  )�  RB  S  Tc   *6�   *�  +j  ,�  -,  -��#  ,  ,,  ,�  -8  -�  0�  3�  46  4r  4�  4�  56  5�  5�  5�  6\  6�  7  7l  7�  84  8�  8�  :�  ;F  ;J  ;�  <z  <�  L�  M  Mj  Mt  M~  Q��  ,@  ,V  1X  1`  1j  Q�  Q��   .Z�   .�
   .�  .�#  .�+  .�d  .��  .�%  .�y  .��  .��  .�b   .�  /  /"  /66   .�o   /�   /&2   /:�   /r  0
  Q��   /�  /��   /�	  0h  0j  ;^  ;l  0l  2  <�  Q�  0n|  0p   0�:   0�T   0�t   0��  0�  Fr  G  1��  1��   1�  ;  <   <4  =  >  Fj  Gz   1�  1�  :n  :~  :�  :�  <�  <�  Bd  B�  G�  G�  L�  O   OF    1�  9p  :X  B�  G�  L�  OJO   1�  1�f   1�  2  2|  2�  3<  3�m3  2  2:  2N  2x  2�  2�  2�  2�  3  38  3L  3b  3�  3�  3�  3�  3�  4  4  4R  4X  4�  4�  4�  4�  5  5  5R  5X  5�  5�  5�  5�  6  6  6z  6�  6�  6�  7&  7,  7�  7�  7�  7�  8R  8X  8�  8�  9  9 �   3�  4*  4f  4�  4�  5*�   5x  5�  5��   6,�  66  6N1   6�O   6�G  6�  6��   7<�  7F  7^]   7�V  7�  7��   8�  8  8&}   8ht  8r  8�   8�  8�  8��  9.  90�  94�  96l  9<  9F  9P  9j  9t  9~  9�  9�  :\  :x  :�  :�  :�z   9B  9�  <�  <�  Bh  G�  O$�   9L�   9f�   9z�   9��   9�%   9��   :�   :e   :r  :�y   :��  :�  ;  ;h�  :��  :��  :��   ;x  ;~�   ;��  ;�  ;�  G�  G�  G��  ;�   ;��   ;��   ;�   ;�0  ;�  N�  O  Q?   ;�  <�  FHG   <  D�T  <(e  <*~   <Rt  <\�  <�  <��  =  B
  N��  =&  =�  C�  D@  D��  =,  =�  C�  DF  N�
   =>  =B  B   B$  BJ  BN  B|  B�  B�  B��   =N�   =R�   =^  =�  =�  C�  Dz  N�  N�   =l  =v  =�  =�  =�    =�  N�   =�  =�  N�  N�)   =�  N�E  >L  >$  >8  A�  PJ�   >|  >�  >�  ?  ?L  ?�  ?�  I�  I�  I�  J*  Jd  J�  J�  K�   >�  >�  >�  ?  ?P  ?�  ?�  ?�  ?�  I�  I�  I�  J.  Jh  J�  J�  K  KH  KL�   >�  I��   >�  PR{   >�  I�  Oj  O~  PV�   >�  >�  ?&  ?Z  ?�  ?�  B�  B�  C2  Cj  I�  I�  J:  Jr  J�  J�  K�   >�  I�  O�  Pl�   >�  I�  O�  Pp�   >�  P��   ?  J
  O�  P�-   ?*  P�'   ?6  JJ  J�  O�  O�  P��   ?^  P�}   ?n  J�  P  P��   ?�  J�  P  P��   ?�  J�  P  P��   ?��   ?�  @�  K*  P4  P��   ?�  B  B<  K8�   @  @  A�  BZ  D  D�  KV  Kn   @  @n  AN  A~  Kj  K�  T$T   @J  A.  EZ  Ez  E�  E�  E�  E�  K�  S�  T   @N  @r  A2  AR  K�  K�   @�  P�@   @�4  A  A�   A�  B �   A�  D��   B.  C�  DZ�   B�  O,�   B�  B�  D"  D�  O  O0  OV�   B�  OR{   B�r   B�  B�  C$  C\a   C
  E^  E��   C(  C`�   CB  E   E~  E�  Q2�   Cz  E<  E�  F  QP�  C�  C�  D8�   C�  D�  H�
   C�  C�  C�  D  DV  Dv  D�  D�  S�  T�  D�  E  F  F$  Q�   E  E  Q  Q&�   E  Q"�   E4  QH9   F�  F�  G  GB  GPW   F�G  F�  F�  F�6  G�  G�  G�  G�J   G�  HZ   G�~  H  H  Hd�   H"�   H0  HP  H��   H4  H|�   H@  Hx  H��   HD  H��   HT  H��   Hj�   H�   H� $  H� ,   H� a  I"  I. l   I�  Oz �   I�  O� �   J>  O� �   Jv  O�!   J�  O�!   J�  P !'   K  P0!b  L  L�  M�!h  L  L�  M�!�   L�!�   L�"   Md"   Mn"   Mx"7   M�"�  N  TH"�  N"�  N"C   N"t   N"X  N"  N,  N8  Nl"|   N(  N<  RH  R�  R�  S$  Sj  T."�   N@"�   ND"�   NX  Q�"�  N�  N�"�  Q|"�  Q�"�  Q�  TD"�  Q�"�  Q�  R "�   R##  R8#)  R:#.  R<#8  R>  S#>  R@  S�  RD  S  T#G  RF  R�  S  S`  T>#M  RJ  R�#W  RL  R�#a  RN  R�  S"  St#f  RP  S&#n  RR#v  RT  S(#�  R�  S�#�  S  S�#�  S#�  S#�   SP#�  SV#�  S|#�  S�$  S�$  S�$  S�#G   T4$<  TF$N  TJ$S  TL$]  T�  T�