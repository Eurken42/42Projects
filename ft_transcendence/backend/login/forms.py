from django.contrib.auth.models import User
from django.contrib.auth.forms import UserCreationForm, AuthenticationForm
from django import forms
from django.forms.widgets import PasswordInput, TextInput


class SignupForm(UserCreationForm):
	username = forms.CharField(max_length=150)
	first_name = forms.CharField(max_length=150)
	last_name = forms.CharField(max_length=150)
	email = forms.EmailField(max_length=150)
	password1 = forms.CharField(max_length=150, widget=forms.PasswordInput)
	password2 = forms.CharField(max_length=150, widget=forms.PasswordInput)
	class Meta:
		model = User
		fields = ['username', 'first_name', 'last_name', 'email', 'password1', 'password2']


class LoginForm(AuthenticationForm):
	username = forms.CharField(widget=TextInput())
	password = forms.CharField(widget=PasswordInput())