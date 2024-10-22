"""
ASGI config for transcendence project.

It exposes the ASGI callable as a module-level variable named ``application``.

For more information on this file, see
https://docs.djangoproject.com/en/4.2/howto/deployment/asgi/
"""

import os

from django.core.asgi import get_asgi_application
from django.urls import path
from channels.routing import ProtocolTypeRouter, URLRouter
from channels.auth import AuthMiddlewareStack
from channels.security.websocket import AllowedHostsOriginValidator
import game.routing
os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'transcendence.settings')

django_asgi_app = get_asgi_application()

application = ProtocolTypeRouter(
	{
		"http" : django_asgi_app,
		"websocket" : AllowedHostsOriginValidator(AuthMiddlewareStack(URLRouter(game.routing.websocket_urlpatterns)))
	}
)


