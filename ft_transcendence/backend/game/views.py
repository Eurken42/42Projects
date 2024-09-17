from django.shortcuts import render, redirect
from django.http import HttpResponse, JsonResponse
from database.models import Games
from rest_framework.decorators import api_view
from rest_framework.response import Response
from rest_framework import status
import json
from django.views.decorators.csrf import csrf_exempt
from django.contrib.auth.forms import UserCreationForm
from django.contrib import messages, auth
from django.shortcuts import render
# Create your views here.


def update_pos(request):
	pass

def render_chat(request, room_name):
	return render(request, 'game/index.html', {"room_name" : room_name})

# Définir les positions initiales des joueurs et de la balle
player1_position = {'x': 0, 'y': 0}
player2_position = {'x': 0, 'y': 0}
ball_position = {'x': 0, 'y': 0}

# Logique de mise à jour des positions
def update_positions():
    # Mettre à jour les positions des joueurs et de la balle ici
    # Exemple simple : Incrémentation de la position de la balle
    ball_position['x'] += 0
    ball_position['y'] += 0

# Endpoint API pour récupérer les positions
def get_positions(request):
    # Mettre à jour les positions avant de les envoyer
    update_positions()
    
    # Créer un dictionnaire contenant les positions actuelles
    positions = {
        'player1': player1_position,
        'player2': player2_position,
        'ball': ball_position
    }
    
    # Envoyer les positions sous forme de réponse JSON
    return JsonResponse(positions)

def render_websocket(request):
      return render(request, "game/websocket.html", {"room_name" : 'chatcool'})
