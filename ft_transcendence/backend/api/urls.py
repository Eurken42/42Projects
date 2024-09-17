from django.urls import path, include
from  . import views

urlpatterns = [
	path("userlist", views.get_user_list),
	path("user/<int:id>", views.user_by_id),
	path("user/create", views.create_new_user),
	path("delete/<int:ind>", views.delete_user_by_id),
	path("gamelist", views.get_game_list),
	path("game/<int:gameid>", views.get_game_by_id),
	path("game/create/", views.create_game),
	path("game/search/", views.search_game),
	path("tournament/create/<int:userid>", views.create_tournament),
	path("tournament/join/<int:tournamentid>/<int:userid>", views.join_tournament),
	path("userprofilelist", views.get_user_profile_list),
	path("tournamentlist", views.get_tournament_list),
	path("history/<int:userid>", views.get_user_history),
	path("update/<int:userid>", views.update_user_info),
	path("√", views.cursed),
	path("send_friend", views.send_friend_request),
	path("accept_friend", views.accept_friend_request),
	path("deny_friend", views.deny_friend_request),
	path("friendlist", views.get_friend_request_list),
	path("get_image/<int:userid>", views.get_picture),
	path("post_image/<int:userid>", views.post_picture),
	path("get_friend/<int:userid>", views.get_friend_info),
	path("update_language/<int:userid>", views.update_language)
	# path('change_password/', views.change_password)
]

