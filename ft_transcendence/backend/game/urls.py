from django.urls import path, include
from  . import views

urlpatterns = [
	path("", views.update_pos),
	path("get_positions", views.get_positions),
	path("websocket", views.render_websocket),
	path("chat/<str:room_name>", views.render_chat)
]
