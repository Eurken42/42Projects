from rest_framework import serializers
from .models import Games, userProfile, Tournament, FriendRequest
from django.contrib.auth.models import User

class UserSerializer(serializers.ModelSerializer):
	class Meta:
		model =  User
		fields = ['id', 'first_name', 'last_name', 'username', 'email', 'is_authenticated']

class GamesSerializer(serializers.ModelSerializer):
	class Meta:
		model = Games
		fields = [ 'p1_id', 'p2_id', 'finished', 'p1_score', 'p2_score','room_group_name', 'room_id', 'date', 'winner_id']

class UserProfileSerializer(serializers.ModelSerializer):
	class Meta:
		model = userProfile
		fields = ['user', 'language','game_won', 'game_lost', 'winrate', 'tournament_alias','tournament_won', 'tournament_lost', 'friendlist', 'online', 'in_game', 'profile_picture']

class TournamentSerializer(serializers.ModelSerializer):
	class Meta:
		model = Tournament
		fields = ['id', 'tournament_id','p1_id', 'p2_id','p3_id', 'p4_id','p1_alias', 'p2_alias','p3_alias', 'p4_alias', 'game1_id', 'game2_id', 'game3_id', 'full', 'finished', 'connected']

class FriendSerializer(serializers.ModelSerializer):
	class Meta:
		model = FriendRequest
		fields = ['id', 'from_user', 'to_user']

