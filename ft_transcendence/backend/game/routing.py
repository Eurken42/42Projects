from django.urls import re_path, path

from . import consumers

websocket_urlpatterns = [
    path("chat/<str:room_name>/", consumers.ChatConsumer.as_asgi()),
	path("game/<int:room_id>/", consumers.AsyncGameConsumer.as_asgi()),
	path("tournament/<int:room_id>/", consumers.AsyncTournamentConsumer.as_asgi()),
]