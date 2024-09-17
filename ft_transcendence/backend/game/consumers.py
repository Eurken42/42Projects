from channels.generic.websocket import WebsocketConsumer, AsyncWebsocketConsumer
import json
import math
import introcs
import asyncio
import time
import threading
from database.models import Games, Tournament, userProfile
from django.contrib.auth.models import User
import channels.layers
from asgiref.sync import async_to_sync, sync_to_async
import random
from channels.db import database_sync_to_async
from.game_class import gameData


gameTab = [None] * 10000
tournament_gametab = [None] * 10000

channel_layer = channels.layers.get_channel_layer()

class AsyncGameConsumer(AsyncWebsocketConsumer):
    def getGame(self):
        return Games.objects.filter(id=1).count()

    def saveGame(self,game):
        game.save()

    async def connect(self):
        self.task = None
        self.room_id = self.scope["url_route"]["kwargs"]["room_id"]
        self.room_group_name = f"game_{self.room_id}"
        await self.accept()
        if gameTab[self.room_id] is None:
            gameTab[self.room_id] = gameData(self.room_id)
            self.game = gameTab[self.room_id]
            self.game.p1id = self.channel_name
            self.game.dbgame = Games(p1_id=-1, p2_id=-1, room_id=self.room_id, room_group_name=self.room_group_name)
            await sync_to_async(self.saveGame)(self.game.dbgame)
            await self.send(text_data=json.dumps({'action' : 'playernumber', 'playernumber' : 1}))
            await self.send(text_data=json.dumps({'action' : 'userid'}))
            # print("GAME P1")
        else:
            self.game = gameTab[self.room_id]
            self.game.p2id = self.channel_name
            self.game.dbgame.full = True
            await sync_to_async(self.saveGame)(self.game.dbgame)
            await self.send(text_data=json.dumps({'action' : 'playernumber', 'playernumber' : 2}))
            await self.send(text_data=json.dumps({'action' : 'userid'}))
            # print("GAME P2")
        
            
        await self.channel_layer.group_add(
            self.room_group_name,
            self.channel_name
        )
        await self.channel_layer.send(
            self.channel_name,
            {
                'type' : 'update',
                "message": {'action' : 'private'}
            }
        )
        if self.channel_name == self.game.p2id:
            await self.channel_layer.group_send(
                self.room_group_name,
                {
                    'type' : 'update',
                    "message": {'action' : 'allin'}
                }
            )

        

    def ball_calc(self):
        pass

    def paddle_calc(self):
        pass

    async def ball_update(self, event):
        ball_position_x = event['bpx']
        ball_position_z = event['bpz']
        await self.channel_layer.group_send(
            self.room_group_name,
            {
                'type' : 'update',
                "message": {'action' : 'ball', 'bx' : ball_position_x, 'bz' : ball_position_z}
            }
        )

    async def stop_game(self):
            await self.channel_layer.group_send(
            self.room_group_name,
            {
                'type' : 'update',
                "message": {'action' : 'Stop', 'scorep1' : self.game.scorep1, 'scorep2' : self.game.scorep2, "winner" : 0}
            }
            )


    async def send_counter(self):
        await asyncio.sleep(1.5)
        for num in range(6, 0, -1):
            await self.channel_layer.group_send(
                self.room_group_name,
                {"type": "update", "message": {'action': 'counter', 'num': num}}
            )
            await asyncio.sleep(1.5)


    async def loop(self):
        await self.send_counter()
        await self.channel_layer.group_send(
        self.room_group_name,
        {"type": "update", "message": {'action' : 'start'}}
        )
        #print("GAME STARTED")
        while self.game.finished == False:
            if self.game.scorep1 == 5 or self.game.scorep2 == 5:
                self.game.finished = True
                self.game.dbgame.finished = True
                self.game.dbgame.p1_score = self.game.scorep1
                self.game.dbgame.p2_score = self.game.scorep2
                await sync_to_async(self.saveGame)(self.game.dbgame)
                await self.stop_game()
            
            paddle_size_x = 0.20000000298023224
            paddle_size_z = 3.1
            #verifier la collision avec le paddle gauche
            if (self.game.bpx - self.game.bradius < self.game.plx + paddle_size_x / 2 and
                self.game.bpx + self.game.bradius > self.game.plx - paddle_size_x / 2 and
                self.game.bpz + self.game.bradius > self.game.plz - paddle_size_z / 2 and
                self.game.bpz - self.game.bradius < self.game.plz + paddle_size_z / 2
                and is_colliding == False):
                # relative_position = (self.game.bpz - self.game.plz) / paddle_size_z
                # angleadjustment = (relative_position - 0.5) * (max_angle_adjustment - min_angle_adjustment) * 0.6
                # Ajuster la direction de la balle en fonction de l'angle
                # angle = math.pi / 4 + angleadjustment
                self.game.bv.x *= -1
                self.game.sif += 0.1
                is_colliding = True
                # #print("collision detectee a gauche")
            #verifier la collision avec le paddle droit
            if (self.game.bpx - self.game.bradius < self.game.prx + paddle_size_x / 2 and
                self.game.bpx + self.game.bradius > self.game.prx - paddle_size_x / 2 and
                self.game.bpz + self.game.bradius > self.game.prz - paddle_size_z / 2 and
                self.game.bpz - self.game.bradius < self.game.prz + paddle_size_z / 2
                and is_colliding == False):
                self.game.bv.x *= -1
                self.game.sif += 0.1
                is_colliding = True
                #self.game.sif += 0.1
                # #print("collision detectee a droite")
            is_colliding = False
            balllimit = 8.5
            if self.game.bpz > balllimit or self.game.bpz < -balllimit:
                self.game.bv.z *= -1
            elif self.game.bpx > 15 or self.game.bpx < -15:
                if self.game.bpx > 15:
                    self.game.scorep2 += 1
                elif self.game.bpx < -15:
                    self.game.scorep1 += 1
                await self.channel_layer.group_send(
                self.room_group_name,
                    {
                        'type' : 'update',
                        "message": {'action' : 'score', 'scorep1' : self.game.scorep1, 'scorep2' : self.game.scorep2}
                    }
                )
                self.game.bpx = 0.0
                self.game.bpz = 0.0
                self.game.sif = 1.05
                self.game.bv = introcs.Vector3(math.cos(1) * 0.17, 0, math.sin(1) * 0.17)
                await self.ball_update({'bpx' : self.game.bpx, 'bpz' : self.game.bpz})
                await asyncio.sleep(1)
    
            self.game.bvx = self.game.bv.x
            self.game.bvz = self.game.bv.z
            self.game.bpx += self.game.bvx
            self.game.bpz += self.game.bvz
            
            await self.ball_update({'bpx' : self.game.bpx, 'bpz' : self.game.bpz})
            await asyncio.sleep(1 / 120)

    async def disconnect(self, close_code):
        self.channel_layer.group_discard(
            self.room_group_name, self.channel_name
        )
        try:
            self.task.cancel()
        except:
            pass
        if self.game.finished == False and self.game.started == True:
            # await self.channel_layer.group_send(
            # self.room_group_name,
            # {"type": "update", "message": {'action' : 'userleave'}}
            # )  
            # await sync_to_async(self.game.dbgame.delete)()
            self.game.dbgame.finished = True
            self.game.dbgame.p1_score = self.game.scorep1
            self.game.dbgame.p2_score = self.game.scorep2
            self.game.dbgame.looser = self.channel_name # A TESTER f sadfdsafsd afads  f asd fad f  ds f ads f ads fasdf ads  f ads f  ads f as f  ads f ad s f asd fads f
            winner = 0
            await sync_to_async(self.saveGame)(self.game.dbgame)
            self.game.finished = True
            user1 = await sync_to_async(User.objects.get)(id=self.game.dbgame.p1_id)
            profile_p1 = await sync_to_async(userProfile.objects.get)(user=user1)
            profile_p1.in_game = False
            await sync_to_async(self.saveGame)(profile_p1)
            user2 = await sync_to_async(User.objects.get)(id=self.game.dbgame.p2_id)
            profile_p2 = await sync_to_async(userProfile.objects.get)(user=user2)
            profile_p2.in_game = False
            await sync_to_async(self.saveGame)(profile_p2)
            if self.channel_name == self.game.p1id:
                profile_p1.game_lost += 1
                profile_p2.game_won += 1
                self.game.dbgame.winner_id = user2.id
                winner = 2
            else:
                profile_p1.game_won += 1
                profile_p2.game_lost += 1
                self.game.dbgame.winner_id = user1.id
                winner = 1
            profile_p1.winrate = round(100 / (profile_p1.game_lost + profile_p1.game_won) * profile_p1.game_won, 2)
            profile_p2.winrate = round(100 / (profile_p2.game_lost + profile_p2.game_won) * profile_p2.game_won, 2)
            profile_p1.in_game = False
            profile_p2.in_game = False
            await sync_to_async(self.saveGame)(profile_p1)
            await sync_to_async(self.saveGame)(profile_p2)
            await sync_to_async(self.saveGame)(self.game.dbgame)
            await self.channel_layer.group_send(
            self.room_group_name,
            {
                'type' : 'update',
                "message": {'action' : 'Stop', 'scorep1' : self.game.scorep1, 'scorep2' : self.game.scorep2, 'winner' : winner}
            }
            )
        else:
            try:
                self.game.finished = True
                self.game.dbgame.finished = True
                await sync_to_async(self.saveGame)(self.game.dbgame)
                user1 = await sync_to_async(User.objects.get)(id=self.game.dbgame.p1_id)
                profile_p1 = await sync_to_async(userProfile.objects.get)(user=user1)
                profile_p1.in_game = False
                await sync_to_async(self.saveGame)(profile_p1)
                user2 = await sync_to_async(User.objects.get)(id=self.game.dbgame.p2_id)
                profile_p2 = await sync_to_async(userProfile.objects.get)(user=user2)
                profile_p2.in_game = False
                await sync_to_async(self.saveGame)(profile_p2)
            except:
                await sync_to_async(self.game.dbgame.delete)()
                profile_p1.in_game = False
                await sync_to_async(self.saveGame)(profile_p1)

    async def receive(self, text_data):
        jsondata = json.loads(text_data)
        message = jsondata['message']
        if message == 'private' or message == 'public':
            if message == 'private':
                self.game.dbgame.private = True
                await sync_to_async(self.saveGame)(self.game.dbgame)
            if self.game.dbgame.full == True:
                self.game.started = True 
        elif message == 'userid':
            user = await sync_to_async(User.objects.get)(id=jsondata['userid'])
            #print(user.username)
            if self.game.p1id == self.channel_name:
                self.game.dbgame.p1_id = jsondata['userid']
                profile_p1 = await sync_to_async(userProfile.objects.get)(user=user)
                profile_p1.in_game = True
                await sync_to_async(self.saveGame)(profile_p1)
            elif self.game.p2id == self.channel_name:
                self.game.dbgame.p2_id = jsondata['userid']
                profile_p2 = await sync_to_async(userProfile.objects.get)(user=user)
                profile_p2.in_game = True
                await sync_to_async(self.saveGame)(profile_p2)
                await self.channel_layer.group_send(
                self.room_group_name,
                {"type": "update", "message": {'action' : 'playerid', 'p1' : self.game.dbgame.p1_id, 'p2' : self.game.dbgame.p2_id}}
                )
            await sync_to_async(self.saveGame)(self.game.dbgame)
        elif message == 'ball_update':
            await self.channel_layer.group_send(
            self.room_group_name,
            {"type": "update", "message": {'action' : 'game', 'bx' : self.game.bpx, 'bz' : self.game.bpz, 'plx' : self.game.plx ,'plz' : self.game.plz, 'prx' : self.game.prx ,'prz' : self.game.prz}}
            )
        elif message == 'getWinner':
            self.game.dbgame = await sync_to_async(Games.objects.get)(room_id=self.room_id) 
            # print(f'self == {self.channel_name}') 
            # print(f'looser == {self.game.dbgame.looser}') # A TESTEER BORDEL
            if self.game.dbgame.looser != '' :
                if self.game.dbgame.looser == self.channel_name:
                    await self.send(text_data=json.dumps({'action' : 'looser'}))
                else:
                    await self.send(text_data=json.dumps({'action' : 'winner'}))
            else:
                if self.game.scorep1 > self.game.scorep2 and self.channel_name == self.game.p1id:
                    await self.send(text_data=json.dumps({'action' : 'winner'}))
                elif self.game.scorep1 < self.game.scorep2 and self.channel_name == self.game.p2id:
                    await self.send(text_data=json.dumps({'action' : 'winner'}))
                else:
                    await self.send(text_data=json.dumps({'action' : 'looser'}))
        elif message == 'mdr':
                user1 = await sync_to_async(User.objects.get)(id=self.game.dbgame.p1_id)
                user2 = await sync_to_async(User.objects.get)(id=self.game.dbgame.p2_id)
                profile_p1 = await sync_to_async(userProfile.objects.get)(user=user1)
                profile_p2 = await sync_to_async(userProfile.objects.get)(user=user2)
                if profile_p1.in_game == True or profile_p2.in_game == True:    
                    if self.game.dbgame.p1_score > self.game.dbgame.p2_score:
                        profile_p1.game_won += 1
                        profile_p2.game_lost += 1
                        self.game.dbgame.winner_id = user1.id
                    else:
                        profile_p2.game_won += 1
                        profile_p1.game_lost += 1
                        self.game.dbgame.winner_id = user2.id
                    profile_p1.winrate = round(100 / (profile_p1.game_lost + profile_p1.game_won) * profile_p1.game_won, 2)
                    profile_p2.winrate = round(100 / (profile_p2.game_lost + profile_p2.game_won) * profile_p2.game_won, 2)
                    profile_p1.in_game = False
                    profile_p2.in_game = False
                    await sync_to_async(self.saveGame)(profile_p1)
                    await sync_to_async(self.saveGame)(profile_p2)
                    await sync_to_async(self.saveGame)(self.game.dbgame)
        elif message == "load":
            self.game.count += 1
            if self.game.count == 2:
                self.task = asyncio.create_task(self.loop())
        elif message == "Stop" or self.game.finished == True:
            try:
                self.task.cancel()
            except:
                pass
        elif message == 'update':
            await self.channel_layer.group_send(
            self.room_group_name,
            {"type": "update", "message": {'action' : 'game', 'bx' : self.game.bpx, 'bz' : self.game.bpz, 'plx' : self.game.plx ,'plz' : self.game.plz, 'prx' : self.game.prx ,'prz' : self.game.prz}}
            )
        elif self.game.p1id == self.channel_name:
            if (message == 'W' or message == 'w' or message == 'Up') and self.game.prz - self.game.ms > -6.5:
                self.game.prz -= self.game.ms
            elif (message == 'S' or message == 's' or message == 'Down') and self.game.prz + self.game.ms < 6.5:
                self.game.prz += self.game.ms
            await self.channel_layer.group_send(
                self.room_group_name,
                {"type": "update", "message": {'action' : 'paddle1', 'prx' : self.game.prx ,'prz' : self.game.prz }}
            )
        elif self.game.p2id == self.channel_name:
            if (message == 'W' or message == 'w' or message == 'Up') and self.game.plz - self.game.ms > -6.5:
                self.game.plz -= self.game.ms
            elif (message == 'S' or message == 's' or message == 'Down') and self.game.plz + self.game.ms < 6.5:
                self.game.plz += self.game.ms
            await self.channel_layer.group_send(
                self.room_group_name,
                {"type": "update", "message": {'action' : 'paddle2', 'plx' : self.game.plx ,'plz' : self.game.plz}}
            )
            

    async def update(self, event):
        data = event['message']
        await self.send(text_data=json.dumps(data))


class AsyncTournamentConsumer(AsyncWebsocketConsumer):

    def saveGame(self,game):
            game.save()
    
    async def connect(self):
        self.tournament_id = self.scope["url_route"]["kwargs"]["room_id"]
        self.room_group_name = f'tournament_{self.tournament_id}'
        self.playerid = 0
        self.playernb = 0
        await self.channel_layer.group_add(
            self.room_group_name,
            self.channel_name
        )
        await self.accept()
        try :
            self.tournoi = await sync_to_async(Tournament.objects.get)(tournament_id=self.tournament_id)
            # print("1")
            if self.tournoi.p2_id == -1:
                #print(self.tournoi.p1_id)
                self.playernb = 1
                user = await sync_to_async(User.objects.get)(id=self.tournoi.p1_id)
                # print("2")
                await self.channel_layer.group_send(
                self.room_group_name,
                {
                'type' : 'update',
                "message": {'action' : 'namep', 'namep' : 1}
                }
                )
            elif self.tournoi.p3_id == -1:
                #print('yes')
                self.playernb = 2
                user = await sync_to_async(User.objects.get)(id=self.tournoi.p2_id)
                # print("3")
                await self.channel_layer.group_send(
                self.room_group_name,
                {
                'type' : 'update',
                "message": {'action' : 'namep', 'namep' : 2}
                }
                )
            elif self.tournoi.p4_id == -1:
                #print('yes')
                self.playernb = 3
                user = await sync_to_async(User.objects.get)(id=self.tournoi.p3_id)
                # print("4")
                await self.channel_layer.group_send(
                self.room_group_name,
                {
                'type' : 'update',
                "message": {'action' : 'namep', 'namep' : 3}
                }
                )
            elif self.tournoi.p4_id != -1:
                #print('All users connected')
                users = []
                self.playernb = 4
                for player_id in [self.tournoi.p1_id, self.tournoi.p2_id, self.tournoi.p3_id, self.tournoi.p4_id]:
                    user = await sync_to_async(userProfile.objects.get)(user=player_id)
                    users.append(user.tournament_alias)
                
                # print("5")
                await self.channel_layer.group_send(
                    self.room_group_name,
                    {
                        'type' : 'update',
                        "message": {'action' : 'all_users', 'users' : users}
                    }
                )
            await self.send(text_data=json.dumps({'message' : self.tournament_id}))
            if self.tournoi.full == True:
                self.playernb = 4
                # print('TOURNAMENT P4')
                user = await sync_to_async(User.objects.get)(id=self.tournoi.p1_id)
                # print("6")
                await self.channel_layer.group_send(
                self.room_group_name,
                {
                'type' : 'update',
                "message": {'action' : 'namep', 'namep' : 4}
                }
                )
                await self.channel_layer.group_send(
                self.room_group_name,
                {
                'type' : 'update',
                "message": {'action' : 'startTournament'}
                }
                )
            await sync_to_async(self.saveGame)(self.tournoi)
            await self.channel_layer.group_send(
            self.room_group_name,
            {
                'type' : 'update',
                "message": {'action' : 'connect', 'connected' : self.playernb}
            }
            )
        except :
            print("except")
            await self.send(text_data=json.dumps({'message' : 'tounamentIdNotFound'}))
            await self.close()

    async def disconnect(self, close_code):
        # print(f'player {self.playernb} disconnected from tournament {self.tournoi.tournament_id}')
        self.tournoi = await sync_to_async(Tournament.objects.get)(tournament_id=self.tournament_id)
        if (self.tournoi.full == False):
            # print(self.tournoi.connected)
            self.tournoi.connected -= 1
            if self.tournoi.connected == 0:
                await sync_to_async(self.tournoi.delete)()
                await self.close()
                return
            # print(self.tournoi.connected)
            await sync_to_async(self.saveGame)(self.tournoi)
            await self.channel_layer.group_send(
            self.room_group_name,
            {
                'type' : 'update',
                "message": {'action' : 'connect', 'connected' : self.tournoi.connected}
            }
            )
            if self.playernb == 1:
                self.tournoi.p1_id = -1
                self.tournoi.p1_alias = ""
            elif self.playernb == 2:
                self.tournoi.p2_id = -1
                self.tournoi.p2_alias = ""
            elif self.playernb == 3:
                self.tournoi.p3_id = -1
                self.tournoi.p3_alias = ""
            elif self.playernb == 4:
                self.tournoi.p4_id = -1
                self.tournoi.p4_alias = ""
            await sync_to_async(self.saveGame)(self.tournoi)
            await self.close()


    async def receive(self, text_data):
        self.tournoi = await sync_to_async(Tournament.objects.get)(tournament_id=self.tournament_id)
        jsondata = json.loads(text_data)
        message = jsondata['message']
        if message == 'getGameId':
            playernb = jsondata['playernb']
            if playernb == '1' or playernb == '3':
                # #print(f'playernb is {playernb}')
                gameid = self.tournoi.game1_id
                await self.send(text_data=json.dumps({'action' : 'gameid', 'gameid' : gameid}))
            elif playernb == '2' or playernb == '4':
                gameid = self.tournoi.game2_id
                await self.send(text_data=json.dumps({'action' : 'gameid', 'gameid' : gameid}))
        elif message == 'winner':
            #print(jsondata['finalid'])
            #print(type(jsondata['finalid']))
            if jsondata['finalid'] == -1:
                #print(f'{self.playernb} has won and can play the final')
                await self.send(text_data=json.dumps({'action' : 'finalid', 'finalid' : self.tournoi.game3_id}))
            else:
                #print(f'tournament is finished, player {self.playernb} has won')
                await self.send(text_data=json.dumps({'action' : 'wonTournament'}))
        elif message == 'looser':
            #print(f'{self.playernb} has lost and cannot play the final')
            await self.disconnect(1)

    async def update(self, event):
        data = event['message']
        await self.send(text_data=json.dumps(data))
    #des la connexion au websocket ouverte, recuperer l'id du joueur afin de set le p2, p3 et p4 id dans l'objet tournoi de la db
    
    
    #quand tout le monde est connecter envoyer un message 
    #ainsi que l'id de la game a chaque joueur pour quils puissent rejoindre la bonne game et set le tournoi a full=True
    #recuperer le gagnant de chaquee game afin de savoir quel joueur aura acces a la finale et disconnect les autres joueur du tournoi

class ChatConsumer(WebsocketConsumer):
    lolmessage = "superlol"
    mdrmessage = "superlolmdr"
    def connect(self):
        self.room_id = self.scope["url_route"]["kwargs"]["room_id"]
        self.room_group_name = "chat_%s" % self.room_id

        # Join room group
        async_to_sync(channel_layer.group_add)(
            self.room_group_name, self.channel_name
        )

        self.accept()


    def test1(self):
        self.lolmessage = "test1"

    def test2(self):
        self.lolmessage = "test2"

    def test3(self):
        self.mdrmessage = "test3"

    def loop(self):
        while True:
            time.sleep(1)
            self.test1()
            self.test2()
            self.test3()
            async_to_sync(channel_layer.group_send)(
                self.room_group_name, {"type": "chat_message", "message": self.lolmessage}
            )

    def disconnect(self, close_code):
        # Leave room group
        async_to_sync(channel_layer.group_discard)(
            self.room_group_name, self.channel_name
        )

    # Receive message from WebSocket
    def receive(self, text_data):
        text_data_json = json.loads(text_data)
        message = text_data_json["message"]

        # Send message to room group
        async_to_sync(channel_layer.group_send)(
            self.room_group_name, {"type": "chat_message", "message": self.mdrmessage}
        )

    # Receive message from room group
    def chat_message(self, event):
        message = event["message"]

        # Send message to WebSocket
        self.send(text_data=json.dumps({"message": message}))
    
class GameConsumer(WebsocketConsumer):
    #     'p1_id' : 1,
    #     'p2_id' : -1,
    #     'finished' : False,
    #     'scoreleft' : 0,
    #     'scoreright' : 0,
    #     'initial_angle' : 0.0,
    #     'self.game.bradius' : 0.5196152629183178,
    #     'ball_position_x' : 0.0,
    #     'ball_position_z' : 0.0,
    #     'ball_velocity_x' : 0.0,
    #     'ball_velocity_z' : 0.0,
    #     'paddleleft_position_x' : -15.0,
    #     'paddleleft_position_z' : 0.0,
    #     'paddleright_position_x' : 15.0,
    #     'paddleright_position_z' : 0.0,
    #     'move_speed' : 0.25,
    #     'speed_increase_factor' : 1.1,
    #     'room_id' : "",
    #     'room_group_name' : ""
    # }

    ball_velocity = introcs.Vector3(math.cos(0) * 0.25, 0, math.sin(0) * 0.25)

    def handle_wall_collision(self):
        balllimit = 8.5
        if self.game.bpz > balllimit or self.game.bpz < -balllimit:
            self.game.bvz *= -1
            # #print("mur")
        elif self.game.bpx > 18 or self.game.bpx < -18:
            if self.game.bpx > 18:
                self.game.scorep2 += 1
            elif self.game.bpx < -18:
                self.game.scorep1 += 1
            self.game.bpx = 0.0
            self.game.bpz = 0.0
            self.game.sif = 1.1
            ball_velocity = introcs.Vector3(math.cos(0) * 0.25, 0, math.sin(0) * 0.25)
    
    def handle_paddle_collision(self):
        self.game.bradius = self.game_values['self.game.bradius']
        paddle_size_x = 0.20000000298023224
        paddle_size_z = 3.1
        max_angle_adjustment = math.pi / 6
        min_angle_adjustment = (math.pi * -1) / 6
        #verifier la collision avec le paddle gauche
        if (self.game.bpx - self.game.bradius < self.game.plx + paddle_size_x / 2 and
            self.game.bpx + self.game.bradius > self.game.plx - paddle_size_x / 2 and
            self.game.bpz + self.game.bradius > self.game.plz - paddle_size_z / 2 and
            self.game.bpz - self.game.bradius < self.game.plz + paddle_size_z / 2
            ):
            relative_position = (self.game.bpz - self.game.plz) / paddle_size_z
            angleadjustment = (relative_position - 0.5) * (max_angle_adjustment - min_angle_adjustment) * 0.6
            # Ajuster la direction de la balle en fonction de l'angle
            angle = math.pi / 4 + angleadjustment
            self.game.bvx = math.cos(angle) * (0.2 * self.game.sif)
            self.game.bvz = math.sin(angle) * (0.2 * self.game.sif)
            self.game.sif += 0.1
            # #print("collision detectee a gauche")
        #verifier la collision avec le paddle droit
        if (self.game.bpx - self.game.bradius < self.game.prx + paddle_size_x / 2 and
            self.game.bpx + self.game.bradius > self.game.prx - paddle_size_x / 2 and
            self.game.bpz + self.game.bradius > self.game.prz - paddle_size_z / 2 and
            self.game.bpz - self.game.bradius < self.game.prz + paddle_size_z / 2
            ):
            relative_position = (self.game.bpz - self.game.prz) / paddle_size_z
            angleadjustment = (relative_position - 0.5) * (max_angle_adjustment - min_angle_adjustment) * 0.3
            # Ajuster la direction de la balle en fonction de l'angle
            angle = (math.pi * -1) / 4 - angleadjustment
            self.game.bvx = (math.cos(angle) * -1) * (0.2 * self.game.sif)
            self.game.bvz = (math.sin(angle) * -1) * (0.2 * self.game.sif)
            self.game.sif += 0.1
            # #print("collision detectee a droite")

    def update_ball_pos(self):
        while self.game_values['finished'] == False:
            time.sleep(0.02)
            self.handle_paddle_collision()
            self.handle_wall_collision()
            self.game.bvx = self.game.bvx
            self.game.bvz = self.game.bvz
            self.game.bpx += self.game.bvx
            self.game.bpz += self.game.bvz
            # #print(self.game.bpx)
            #self.send(text_data=json.dumps(self.game_values))
            # async_to_sync(self.channel_layer.group_send)(self.randname, {"type" : "testsend", "game_data" : self.game_values})
            async_to_sync(channel_layer.group_send)(
             self.room_group_name, {"type": "chat_message", "message": self.game_values}
            )

    def update_right_paddle_pos(self, message):
        if message == 'Up' and self.game.prz - self.game.ms > -6.5:
            self.game.prz -= self.game.ms
        elif message == 'Down' and self.game.prz + self.game.ms < 6.5:
            self.game.prz += self.game.ms

    def connect(self):
        self.room_id = self.scope["url_route"]["kwargs"]["room_id"]
        self.room_group_name = "chat_%s" % self.room_id
        self.game_values = {
            'p1_id' : 1,
            'p2_id' : -1,
            'finished' : False,
            'scoreleft' : 0,
            'scoreright' : 0,
            'initial_angle' : 0.0,
            'self.game.bradius' : 0.5196152629183178,
            'ball_position_x' : 0.0,
            'ball_position_z' : 0.0,
            'ball_velocity_x' : 0.0,
            'ball_velocity_z' : 0.0,
            'paddleleft_position_x' : -15.0,
            'paddleleft_position_z' : 0.0,
            'paddleright_position_x' : 15.0,
            'paddleright_position_z' : 0.0,
            'move_speed' : 0.25,
            'speed_increase_factor' : 1.1,
            'channel_name' : self.channel_name
        }
        self.game_values['room_id'] = self.room_id
        self.game_values['room_group_name'] = self.room_group_name
        # Join room group
        async_to_sync(channel_layer.group_add)(
        self.room_group_name, self.channel_name
        )
        self.accept()
        threading.Thread(target=self.update_ball_pos).start()


    def disconnect(self, close_code):
        async_to_sync(channel_layer.group_discard)(
            self.room_group_name, self.channel_name
        )
        # game = Games(player1=User.objects.get(id=self.game_values['p1_id']), p1_score=self.game.scorep2, p2_score=self.game.scorep1)
        # game.save()
        #async_to_sync(self.channel_layer.group_add)(self.randname), self.channel_name)
        pass

    def receive(self, text_data):
        #while self.game_values['finished'] == False:
        text_data_json = json.loads(text_data)
        message = text_data_json["message"]
        ##print(message)
        if message == 'Stop':
            self.game_values['finished'] = True
        elif message == 'IA':
            pos = text_data_json['pos']
            self.game.plz = float(pos)
        else:
            self.update_right_paddle_pos(message)
        # async_to_sync(channel_layer.group_send)(
        #      self.room_group_name, {"type": "chat_message", "message": self.game_values}
        #  )
    
    def chat_message(self, event):
        data = event["message"]
        self.send(text_data=json.dumps(data))

        
    # finished = False
    # scoreleft = 0
    # scoreright = 0
    # ball_position_x = 0.0
    # ball_position_z = 0.0
    # ball_velocity_x = 0.0
    # ball_velocity_z = 0.0
    # paddleleft_position_x = 0.0
    # paddleleft_position_z = 0.0
    # paddleright_position_x = 0.0
    # paddleright_position_z = 0.0
    # move_speed = 0.1
        