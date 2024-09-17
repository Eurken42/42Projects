from django.urls import path, include
from  . import views

urlpatterns = [
	path("", views.login_form, name="login_form"),
	path("register/", views.register, name="register"),
	path("home/", views.home_page, name="home_page"),
	path("logout/<int:id>", views.logout, name="logout"),
	path("login/", views.login, name="login"),
	path("session_user/", views.get_session_username)
]
