SuperStrict

Import BaH.Raknet

Import "source.bmx"


Extern

	Function bmx_raknetroomsplugin_new:Byte Ptr()
	Function bmx_raknetroomsplugin_SetOrderingChannel(handle:Byte Ptr, oc:Int)
	Function bmx_raknetroomsplugin_SetSendPriority(handle:Byte Ptr, pp:Int)
	Function bmx_raknetroomsplugin_ClearRoomMembers(handle:Byte Ptr)
	Function bmx_raknetroomsplugin_ClearLoginServerAdddresses(handle:Byte Ptr)

End Extern



Const RPO_CREATE_ROOM:Int = 0
Const RPO_ENTER_ROOM:Int = 1
Const RPO_JOIN_BY_FILTER:Int = 2
Const RPO_LEAVE_ROOM:Int = 3
Const RPO_GET_INVITES_TO_PARTICIPANT:Int = 4
Const RPO_SEND_INVITE:Int = 5
Const RPO_ACCEPT_INVITE:Int = 6
Const RPO_START_SPECTATING:Int = 7
Const RPO_STOP_SPECTATING:Int = 8
Const RPO_GRANT_MODERATOR:Int = 9
Const RPO_CHANGE_SLOT_COUNTS:Int = 10
Const RPO_SET_CUSTOM_ROOM_PROPERTIES:Int = 11
Const RPO_CHANGE_ROOM_NAME:Int = 12
Const RPO_SET_HIDDEN_FROM_SEARCHES:Int = 13
Const RPO_SET_DESTROY_ON_MODERATOR_LEAVE:Int = 14
Const RPO_SET_READY_STATUS:Int = 15
Const RPO_GET_READY_STATUS:Int = 16
Const RPO_SET_ROOM_LOCK_STATE:Int = 17
Const RPO_GET_ROOM_LOCK_STATE:Int = 18
Const RPO_ARE_ALL_MEMBERS_READY:Int = 19
Const RPO_KICK_MEMBER:Int = 20
Const RPO_UNBAN_MEMBER:Int = 21
Const RPO_GET_BAN_REASON:Int = 22
Const RPO_ADD_USER_TO_QUICK_JOIN:Int = 23
Const RPO_REMOVE_USER_FROM_QUICK_JOIN:Int = 24
Const RPO_IS_IN_QUICK_JOIN:Int = 25
Const RPO_SEARCH_BY_FILTER:Int = 26
Const RPO_CHANGE_HANDLE:Int = 27
Const RPO_ROOM_CHAT:Int = 28
Const RPN_QUICK_JOIN_EXPIRED:Int = 29
Const RPN_QUICK_JOIN_ENTERED_ROOM:Int = 30
Const RPN_ROOM_MEMBER_STARTED_SPECTATING:Int = 31
Const RPN_ROOM_MEMBER_STOPPED_SPECTATING:Int = 32
Const RPN_MODERATOR_CHANGED:Int = 33
Const RPN_SLOT_COUNTS_SET:Int = 34
Const RPN_CUSTOM_ROOM_PROPERTIES_SET:Int = 35
Const RPN_ROOM_NAME_SET:Int = 36
Const RPN_HIDDEN_FROM_SEARCHES_SET:Int = 37
Const RPN_ROOM_MEMBER_READY_STATUS_SET:Int = 38
Const RPN_ROOM_LOCK_STATE_SET:Int = 39
Const RPN_ROOM_MEMBER_KICKED:Int = 40
Const RPN_ROOM_MEMBER_HANDLE_SET:Int = 41
Const RPN_ROOM_MEMBER_LEFT_ROOM:Int = 42
Const RPN_ROOM_MEMBER_JOINED_ROOM:Int = 43
Const RPN_ROOM_INVITATION_SENT:Int = 44
Const RPN_ROOM_INVITATION_WITHDRAWN:Int = 45
Const RPN_ROOM_DESTROYED_ON_MODERATOR_LEFT:Int = 46
Const RPN_ROOM_CHAT_NOTIFICATION:Int = 47


