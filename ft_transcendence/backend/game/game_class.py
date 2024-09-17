import introcs
import math
import random

class gameData:
	def __init__(self, id):
		self.bv = introcs.Vector3(0, 0, 0)
		self.id = id
		self.count = 0
		self.finished = False
		self.started = False
		self.p1id = -1
		self.p2id = -1
		self.scorep1 = 0
		self.scorep2 = 0
		# Générer un angle aléatoire entre 40 et 60 degrés pour la première direction
		angle1_deg = random.uniform(40, 60)
		angle1_rad = math.radians(angle1_deg)
		# Calculer les composantes x et z de la vitesse de la balle pour la première direction
		bv1_x = math.cos(angle1_rad) * 0.17
		bv1_z = math.sin(angle1_rad) * 0.17
		# Générer un angle aléatoire entre 120 et 140 degrés pour la deuxième direction
		angle2_deg = random.uniform(120, 140)
		angle2_rad = math.radians(angle2_deg)
		# Calculer les composantes x et z de la vitesse de la balle pour la deuxième direction
		bv2_x = math.cos(angle2_rad) * 0.17
		bv2_z = math.sin(angle2_rad) * 0.17
		# Sélectionner aléatoirement l'une des deux directions pour le départ de la balle
		if random.choice([True, False]):
			self.bv.x = bv1_x
			self.bv.z = bv1_z
		else:
			self.bv.x = bv2_x
			self.bv.z = bv2_z
		self.bradius = 0.7 # ball radius
		self.bpx = 0.0 # ball position x
		self.bpz = 0.0 # ball position z
		self.plx = -15.0 # paddle left position x
		self.plz = 0.0 # paddle left position z
		self.prx = 15 # paddle right position x
		self.prz = 0.0 # paddle right position z
		self.ms = 0.3 # move speed
		self.sif = 0.4 # speed increase factor
		self.dbgame = None
		

	
