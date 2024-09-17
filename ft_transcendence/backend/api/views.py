from django.shortcuts import render, redirect
from django.contrib.auth.hashers import make_password
from django.http import HttpResponse, JsonResponse
from database.models import  Games, Tournament, userProfile, FriendRequest
from database.serializers import UserSerializer, GamesSerializer, UserProfileSerializer, TournamentSerializer, FriendSerializer
from rest_framework.decorators import api_view
from rest_framework.response import Response
from rest_framework import status
import re
import json
from django.views.decorators.csrf import csrf_exempt, ensure_csrf_cookie
from django.contrib.auth.forms import UserCreationForm
from django.contrib import messages, auth
from django.shortcuts import render
from django.contrib.auth.models import User
from django.conf import settings
from django.db.models import Q
import random, os
from itertools import chain
from django.contrib.auth.decorators import login_required

@api_view(['GET'])
def get_user_list(request):
	# print('##########')
	# A RAJOUTER AU MOMENT DU RENDU
	if request.user.is_anonymous == True:
		return HttpResponse('Forbidden', status=403)
	if (request.method == 'GET'):
		users = User.objects.all()
		serializer = UserSerializer(users, many=True)
		return Response(serializer.data)
	else:
		return Response("Unauthorized method", status=status.HTTP_401_UNAUTHORIZED)

@api_view(['GET'])
def get_user_profile_list(request):
	if request.user.is_anonymous == True:
		return HttpResponse('Forbidden', status=403)
	if (request.method == 'GET'):
		profiles = userProfile.objects.all()
		serializer = UserProfileSerializer(profiles, many=True)
		return Response(serializer.data)
	else:
		return Response("Unauthorized method", status=status.HTTP_401_UNAUTHORIZED)

#Either returns the user with the specified id or update the user specified by id in the database
@api_view(['GET', 'PUT'])
def user_by_id(request, id):
	if request.user.is_anonymous == True:
		return HttpResponse('Forbidden', status=403)
	if (request.method == 'GET'):
		user = User.objects.get(id=id)
		serializer = UserSerializer(user)
		return Response(serializer.data, status=status.HTTP_200_OK)
	elif (request.method == 'PUT'):
		queryset = User.objects.filter(id=id)
		serializer = UserSerializer(data=request.data)
		if serializer.is_valid():
			user = queryset[0]
			user.first_name = serializer.data['first_name']
			user.last_name = serializer.data['last_name']
			user.username = serializer.data['username']
			user.email = serializer.data['email']
			user.password = serializer.data['password']
			user.save(update_fields=['first_name', 'last_name', 'username', 'email'])
			return Response(serializer.data, status=status.HTTP_200_OK)
	else:
		return Response("Method not allowed", status=status.HTTP_405_METHOD_NOT_ALLOWED)

#Create a new user in the database with the attributes specified in the form
@api_view(['POST'])
def create_new_user(request):
	if request.user.is_anonymous == True:
		return HttpResponse('Forbidden', status=403)
	if request.method == 'POST':
		serializer = UserSerializer(data=request.data)
		if serializer.is_valid():
			user = User.objects.filter(login=serializer.data['login'])
			if not user.exists():
				user = User(name=serializer.data['name'], login=serializer.data['login'], password=serializer.data['password'])
				user.save()
				return Response("User " + serializer.data['login'] + " has been added to database", status=status.HTTP_201_CREATED)
			else:
				return Response("User with login " + serializer.data['login'] + " already exists in the database", status=status.HTTP_409_CONFLICT)
		else:
			return Response("Data of new user is not valid", status=status.HTTP_400_BAD_REQUEST)
	else:
		return Response("Method not allowed", status=status.HTTP_405_METHOD_NOT_ALLOWED)

#Delete user with specified id from the database
@api_view(['DELETE'])
def delete_user_by_id(request, id):
	if request.user.is_anonymous == True:
		return HttpResponse('Forbidden', status=403)
	if request.method == "DELETE":
		queryset = User.objects.filter(id=id)
		if queryset.exists():
			user = queryset[0]
			user.delete()
			return Response("User with id " + str(id) + " was successfuly deleted from the database", status=status.HTTP_200_OK)
		else:
			return Response("User with id " + str(id) + " was not found in the database", status=status.HTTP_404_NOT_FOUND)
	else:
		return Response("Method not allowed", status=status.HTTP_405_METHOD_NOT_ALLOWED)


@api_view(['GET'])
def get_game_list(request):
	if request.user.is_anonymous == True:
		return HttpResponse('Forbidden', status=403)
	if (request.method == 'GET'):
		games = Games.objects.all()
		serializer = GamesSerializer(games, many=True)
		return Response(serializer.data)
	else:
		return Response("Unauthorized method", status=status.HTTP_401_UNAUTHORIZED)
	
@api_view(['GET'])
def get_game_by_id(request, gameid):
	if request.user.is_anonymous == True:
		return HttpResponse('Forbidden', status=403)
	if (request.method == 'GET'):
		game = Games.objects.filter(room_id=gameid, private=True, finished=False, started=False).count()
		if game == 0:
			return Response({"message" : "Not found"})
		else:
			try:
				game = Games.objects.get(room_id=gameid, finished=False, private=True)
				serializer = GamesSerializer(game)
				return Response({"message" : serializer.data})
			except:
				return Response({"message" : "Game is already finished"})
	else:
		return Response("Unauthorized method", status=status.HTTP_401_UNAUTHORIZED)
	

@api_view(['GET'])
def create_game(request):
	if request.user.is_anonymous == True:
		return HttpResponse('Forbidden', status=403)
	if request.method == 'GET':
		newid = random.randint(1, 9999)
		while Games.objects.filter(room_id=newid).count() != 0:
			newid = random.randint(1, 9999)
		return Response({"message" : "ok", 'id' : newid}, status=status.HTTP_200_OK)
	else:
		return Response("Unauthorized method", status=status.HTTP_401_UNAUTHORIZED)

@api_view(['GET'])
def search_game(request):
	if request.user.is_anonymous == True:
		return HttpResponse('Forbidden', status=403)
	if request.method == 'GET':
		while True:
			try:
				games = Games.objects.filter(started=False, finished=False, full=False, private=False)
				id = games[0].room_id
				return Response({"message" : "ok", 'id' : id})
			except:
				newid = random.randint(1, 9999)
				while Games.objects.filter(room_id=newid).count() != 0:
					newid = random.randint(1, 9999)
				return Response({"message" : "ok", 'id' : newid}, status=status.HTTP_200_OK)
	else:
		return Response("Unauthorized method", status=status.HTTP_401_UNAUTHORIZED)
	

@api_view(['GET'])
def create_tournament(request, userid):
	if request.user.is_anonymous == True:
		return HttpResponse('Forbidden', status=403)
	if request.method == 'GET':
		profile = userProfile.objects.get(user=User.objects.get(id=userid))
		tournamentid = create_random_tournament_id(1, 9999)
		game1id = create_random_game_id(1, 9999)
		game2id = create_random_game_id(1, 9999)
		game3id = create_random_game_id(1, 9999)
		tournoi = Tournament(p1_id=userid, p1_alias=profile.tournament_alias, game1_id=game1id, game2_id=game2id, game3_id=game3id, tournament_id=tournamentid)
		tournoi.connected += 1
		tournoi.save()
		return Response({'tournamentid' : tournamentid, 'game1id' : game1id, 'game2id' : game2id, 'game3id' : game3id, 'playernb' : 1})
	else:
		return Response("Unauthorized method", status=status.HTTP_401_UNAUTHORIZED)
	
@api_view(['POST'])
def join_tournament(request, tournamentid, userid):
	if request.user.is_anonymous == True:
		return HttpResponse('Forbidden', status=403)
	if request.method == 'POST':
		profile = userProfile.objects.get(user=User.objects.get(id=userid))
		playernb = 0
		try:
			qs = Tournament.objects.filter(tournament_id=tournamentid, full=False, finished=False)
			tournoi = qs[0]
			if tournoi.p1_id == -1:
				tournoi.p1_id = userid
				tournoi.p1_alias = profile.tournament_alias
				playernb = 1
			elif tournoi.p2_id == -1:
				tournoi.p2_id = userid
				tournoi.p2_alias = profile.tournament_alias
				playernb = 2
			elif tournoi.p3_id == -1:
				playernb = 3
				tournoi.p3_id = userid
				tournoi.p3_alias = profile.tournament_alias
			else:
				tournoi.full = True
				playernb = 4
				tournoi.p4_id = userid
				tournoi.p4_alias = profile.tournament_alias
			tournoi.connected += 1
			tournoi.save()
			return Response({'message' : 'ok', 'game1id' : tournoi.game1_id, 'game2id' : tournoi.game2_id, 'game3id' : tournoi.game3_id, 'playernb' : playernb})
		except:
			return Response({'message' : 'ko'}, status=status.HTTP_404_NOT_FOUND)
	else:
		return Response("Unauthorized method", status=status.HTTP_401_UNAUTHORIZED)
	

def create_random_game_id(start, end):
	newid = random.randint(start, end)
	while Games.objects.filter(room_id=newid, finished=False).count() != 0:
		newid = random.randint(start, end)
	return newid

def create_random_tournament_id(start, end):
	newid = random.randint(start, end)
	while Tournament.objects.filter(tournament_id=newid, finished=False).count() != 0:
		newid = random.randint(start, end)
	return newid

@api_view(['GET'])
def get_tournament_list(request):
	if request.user.is_anonymous == True:
		return HttpResponse('Forbidden', status=403)
	if (request.method == 'GET'):
		tournaments = Tournament.objects.all()
		serializer = TournamentSerializer(tournaments, many=True)
		return Response(serializer.data)
	else:
		return Response("Unauthorized method", status=status.HTTP_401_UNAUTHORIZED)
	

@api_view(['GET'])
def get_user_history(request, userid):
	if request.user.is_anonymous == True:
		return HttpResponse('Forbidden', status=403)
	if (request.method == 'GET'):
		games1 = Games.objects.filter(p1_id=userid)
		games2 = Games.objects.filter(p2_id=userid)
		serializer1 = GamesSerializer(games1, many=True)
		serializer2 = GamesSerializer(games2, many=True)
		return Response({'message' : 'OK', 'data' : serializer1.data + serializer2.data}, status=200)
	else:
		return Response("Unauthorized method", status=status.HTTP_401_UNAUTHORIZED)

@api_view(['PUT'])
def update_user_info(request, userid):
	if request.user.is_anonymous == True:
		return HttpResponse('Forbidden', status=403)
	if request.method == 'PUT':
		error = 0
		try:
			data = json.loads(request.body)
			user = User.objects.get(id=userid)
			profile = userProfile.objects.get(user=user)
			# print(data)
			alias = data['alias']
			username = data['username']
			email = data['email']
			first_name = data['first_name']
			last_name = data['last_name']
			password = data['password']
			if username != user.username and username != '':
				if not User.objects.filter(username=username).exists():
					user.username = username
				else:
					error = 1
			if alias != profile.tournament_alias and alias != '':
				if not userProfile.objects.filter(tournament_alias=alias).exists():
					profile.tournament_alias = alias
				else:
					error = 1
			if email != user.email and email != '':
				email_regex = r'^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$'
				if not User.objects.filter(email=email).exists() and re.match(email_regex, email):
					user.email = email
				else:
					error = 1
			if password != '' and make_password(password) != user.password:
				password_regex = r'^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)[A-Za-z\d\W_]{8,20}$'
				if not re.match(password_regex, password):
					error = 1
				else:
					user.password = make_password(password)
			if last_name != '':
				user.last_name = last_name
			if  first_name != '':
				user.first_name = first_name
			if error == 0:
				user.save()
				profile.save()
				return Response({'message' : 'OK'}, status=200)
			else:
				return Response({'message' : 'KO'}, status=400)
		except:
			return Response({'message' : 'KO'}, status=400)
	else:
		return Response({'message' 'KO'}, status=405)
		

def update_language(request, userid):
	if request.user.is_anonymous == True:
		return HttpResponse('Forbidden', status=403)
	if request.method == 'POST':
		try:
			data = json.loads(request.body)
			newlanguage = int(data['language'])
			user = User.objects.get(id=userid)
			profile = userProfile.objects.get(user=user)
			profile.language = newlanguage
			profile.save()
			return JsonResponse({"message" : "OK"}, status=201)
		except:
			return JsonResponse({"message" : "KO"}, status=405)	
	else:
		return JsonResponse({"message" : "KO"}, status=405)


@ensure_csrf_cookie
def cursed(request):
	return HttpResponse("", status=200)

def send_friend_request(request):
	if request.user.is_anonymous == True:
		return HttpResponse('Forbidden', status=403)
	#print(request.user.is_anonymous)
	try:
		data = json.loads(request.body)
		from_id = data['username']
		to_username = data['password']
		#print(from_id)
		#print(to_username)
		from_user = User.objects.get(id=from_id)
		to_user = User.objects.get(username=to_username)

		friend_request, created = FriendRequest.objects.get_or_create(from_user=from_user, to_user=to_user)
		if created:
			return JsonResponse({'message' : 'OK', 'info' : 'request sent'}, status=201)
		else:
			return JsonResponse({'message' : 'KO', 'info' : 'request was already sent'}, status=200)
	except:
		return JsonResponse({'message' : 'KO', 'info' : 'user did not exist'}, status=404)
	
def accept_friend_request(request):
	if request.user.is_anonymous == True:
		return HttpResponse('Forbidden', status=403)
	try:
		data = json.loads(request.body)
		#print(data)
		userid = int(data['username'])
		requestid = int(data['password'])
		#print('#####################')
		#print(userid)
		#print(requestid)
		# verify that friend request is not from same user that sent it
		friend_request = FriendRequest.objects.get(id=requestid)
		#print(friend_request.to_user)
		#print(friend_request.to_user.id)
		if friend_request.from_user.id == userid:
			from_user = userProfile.objects.get(user=friend_request.from_user)
			to_user = userProfile.objects.get(user=friend_request.to_user)
			from_user.friendlist.add(to_user.user)
			to_user.friendlist.add(from_user.user)
			friend_request.delete()
			return JsonResponse({'message' : 'OK', 'info' : 'request accepted'}, status=201)
		else:
			return JsonResponse({'message' : 'KO', 'info' : 'user / request did not exist'}, status=404)	
	except:
		return JsonResponse({'message' : 'KO', 'info' : 'user / request did not exist'}, status=404)
	
def deny_friend_request(request):
	if request.user.is_anonymous == True:
		return HttpResponse('Forbidden', status=403)
	try:
		data = json.loads(request.body)
		userid = int(data['username'])
		requestid = int(data['password'])
		#print(requestid)
		#print(userid)
		friend_request = FriendRequest.objects.get(id=requestid)
		if friend_request.to_user.id == userid:
			friend_request.delete()
			return JsonResponse({'message' : 'OK', 'info' : 'request denied'}, status=201)
		else:
			return JsonResponse({'message' : 'KO', 'info' : 'user / request did not exist'}, status=404)
	except:
		return JsonResponse({'message' : 'KO', 'info' : 'user / request did not exist'}, status=404)

@api_view(['GET'])
def get_friend_request_list(request):
	if request.user.is_anonymous == True:
		return HttpResponse('Forbidden', status=403)
	if (request.method == 'GET'):
		users = FriendRequest.objects.all()
		serializer = FriendSerializer(users, many=True)
		return Response(serializer.data)
	else:
		return Response("Unauthorized method", status=status.HTTP_401_UNAUTHORIZED)
	

def get_picture(request, userid):
	if request.user.is_anonymous == True:
		return HttpResponse('Forbidden', status=403)
	if request.method == 'GET':
		try:
			user = User.objects.get(id=userid)
			profile = userProfile.objects.get(user=user)
			image_path = os.path.join(settings.MEDIA_ROOT, 'media/images', profile.profile_picture.url)
			#print(image_path)
			with open(f'media/{image_path}', 'rb') as f:
				return HttpResponse(f.read(), content_type='image/jpeg')  # Assurez-vous d'ajuster le type MIME en fonction du type d'image que vous stockez
		except IOError:
			return HttpResponse(status=404)
	else:
		return JsonResponse({'message': 'Méthode non autorisée'}, status=405)

def post_picture(request, userid):
	if request.user.is_anonymous == True:
		return HttpResponse('Forbidden', status=403)
	if request.method == 'POST':
		user = User.objects.get(id=userid)
		profile = userProfile.objects.get(user=user)
		image = request.FILES.get('filename')
		if image:
			profile.profile_picture = image
			image_url = profile.profile_picture.url
			profile.save()
			return JsonResponse({'message': 'Image sauvegardée avec succès', 'image_url': image_url})
		else:
			return JsonResponse({'message': 'Aucune image reçue'}, status=400)
	else:
		return JsonResponse({'message': 'Méthode non autorisée'}, status=405)

def get_friend_info(request, userid):
	if request.user.is_anonymous == True:
		return HttpResponse('Forbidden', status=403)
	if request.method == 'GET':
		try:
			friendinfo = {}
			
			user = User.objects.get(id=userid)
			profile = userProfile.objects.get(user=user)
			
			games = Games.objects.filter(Q(p1_id=userid) | Q(p2_id=userid)).order_by('date')
			serializer = GamesSerializer(games, many=True)
			
			for game in range(0, 10):
				if game >= 10:
					break
				if games.count() > game:
					serializer = GamesSerializer(games[game], many=False)
					friendinfo[f'game_{game + 1}'] = serializer.data
				else:
					friendinfo[f'game_{game + 1}'] = 'NULL'

				friendinfo['winrate'] = profile.winrate
				friendinfo['total_games'] = profile.game_lost + profile.game_won
				if profile.in_game == True:
					friendinfo['state'] = 'In Game'
				elif profile.online == True:
					friendinfo['state'] = 'Online'
				else:
					friendinfo['state'] = 'Offline'
				friendinfo['username'] = user.username
				friendinfo['alias'] = profile.tournament_alias

			return JsonResponse({'message' : friendinfo}, status=200)
		except:
			return JsonResponse({'message': 'User does not exists'}, status=404)	
	else:
		return JsonResponse({'message': 'Méthode non autorisée'}, status=405)
