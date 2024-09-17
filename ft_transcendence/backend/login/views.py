from django.shortcuts import render
from database.models import Games, userProfile
from django.shortcuts import render, redirect
from rest_framework.response import Response
from rest_framework import status
from django.http import	HttpResponse, JsonResponse
from django.contrib import messages, auth
from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.models import User
from django.contrib.auth.forms import UserCreationForm
from .forms import SignupForm, LoginForm
from django.http import JsonResponse
import json
from database.serializers import UserSerializer
from django.contrib.auth.hashers import make_password
from django.views.decorators.csrf import ensure_csrf_cookie
import re


def home_page(request):
	return render(request, "login/home.html")

def parse_and_validate(data):
	data = data.strip()
	# print(data)
	data_regex = r'^(?!.*\s{2})(?!.*\b\w{26,}).{1,25}$';
	if not data or not re.match(data_regex, data):
		return False
	return data

@ensure_csrf_cookie
def register(request):
	if request.method == 'POST':
		#Check + parse data
		username = parse_and_validate(request.POST['username'])
		if username == False:
			return JsonResponse({ "message" : "KO", "info" : "usernameError"}, status=422)
		first_name = parse_and_validate(request.POST['first_name'])
		if first_name == False:
			return JsonResponse({ "message" : "KO", "info" : "firstNameError"}, status=422)
		last_name = parse_and_validate(request.POST['last_name'])
		alias_tournament = parse_and_validate(request.POST['alias'])
		# ['alias']
		if last_name == False:
			return JsonResponse({ "message" : "KO", "info" : "lastNameError"}, status=422)
		email_regex = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
		email = request.POST['email'].strip()
		if not re.match(email_regex, email):
			return JsonResponse({ "message" : "KO", "info" : "emailError"}, status=422)
		if request.POST['password1'] != request.POST['password2']:
			return JsonResponse({ 'message' : 'passwordMatchError'}, status=422)
		else:
			password_regex = r'^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)[A-Za-z\d\W_]{8,20}$'
			if not re.match(password_regex, request.POST['password1']):
				return JsonResponse({ "message" : "KO", "info" : "passwordSyntaxError"}, status=422)
		if User.objects.filter(username=username).exists() or User.objects.filter(email=email).exists() or userProfile.objects.filter(tournament_alias=alias_tournament).exists():
			return JsonResponse({ "message" : "KO", "info" : "account wiht same username / alias / email alread exists"}, status=409)
		else:
			user = User.objects.filter(username=username)
			password = make_password(request.POST['password1'])
			user = User(username=username, first_name=first_name,  last_name=last_name, email=email, password=password)
			user.save()
			userprofile = userProfile(user=user, tournament_alias=alias_tournament)
			userprofile.save()
			return JsonResponse({ "message" : "OK", "info" : "signupOk"}, status=201)
	else:
		return JsonResponse({ "message" : "Method not allowed"}, status=405)

@ensure_csrf_cookie
def login(request):
	if request.method == 'POST':
		data = json.loads(request.body)
		username = data['username']
		password = data['password']
		user = authenticate(username=username, password=password)
		if user is not None:
			auth.login(request, user)
			user = User.objects.get(username=username)
			userprofile = userProfile.objects.get(user=user)
			if userprofile.online == True:
				return JsonResponse({"message" : 'KO'}, status=403)	
			userprofile.online = True
			userprofile.save()
			return JsonResponse({"message" : "OK", "id" : user.id, "username" : user.username, "first_name" : user.first_name, "last_name" : user.last_name, "email" : user.email, "language" : userprofile.language}, status=201)
		else:
			return JsonResponse({"message" : 'KO'}, status=404)
	else:
		return JsonResponse({"message" : "KO"}, status=405)

def logout(request, id):
	if request.user.is_anonymous == True:
		return HttpResponse('Forbidden', status=403)
	user = User.objects.get(id=id)
	if user.is_authenticated:
		# print("ihgsdfuisdgfuharsgvrvauhcguaecgjesabcjawebrj awebfbasdjfbsadj fvbjsd  vfjasdfvasdjfvhasd vfhasdvfhasd vfhasdvfh asdvhgf vasdhgvfhgsa fhasd ajsdfchdsc hashjwh fhgaf hav hfwveh fbv qwhbfwqehf wehqbf wheqbf whqekb fhqbkwe fhkqwe fkhqw fhkqwe fqwehk fqwhek fhqwe fhkbqwe fhkbqwe fhkbqwe fhkbqwe fhkbqwe fhbqwe fkhbqwe fkhbqw efhbqw  hfbqw  fhbqw e hfbqw e hfb qweh bf qweh fqweh bfqwehb fwqehb fhb")
		userprofile = userProfile.objects.get(user=user)
		userprofile.online = False
		userprofile.save()
		auth.logout(request)
		return JsonResponse({"message" : "OK"})
	else:
		return JsonResponse({"message" : "KO"})

def login_form(request):
	form = LoginForm()
	if request.method == 'POST':
		# print(request.POST)
		form = LoginForm(request, data=request.POST)
		if form.is_valid():
			username = request.POST['username']
			password = request.POST['password']

			user = authenticate(request, username=username, password=password)

			if user is not None:
				auth.login(request, user)
				return redirect("home_page")
			else:
				return redirect("login/login.html")
		else:
			return JsonResponse({"message" : "error"})
	return render(request, "login/login.html", {'form' : form})
		


	
def get_session_username(request):
	return JsonResponse({'user_id' : request.session['user_id']})

# LOGIN form -> if method == get render login form else if method == post login user
# REGISTER form -> if method == get render register form else if method == post create new user in database
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
