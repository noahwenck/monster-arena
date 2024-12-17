from enum import Enum

class Monster:
    def __init__(self, team, health, damage, dead=False):
        self.dead = dead
        self.team = team
        self.health = health
        self.damage = damage

    def attack(self, target):
        if isinstance(target, Orc):
            dealed_damage = self.damage - target.damage_blocked
            print(f"{self.team.name} {type(self).__name__} attacks {target.team.name} {type(target).__name__} "
                  f"for {self.damage}, dealing {dealed_damage} damage, and receiving {target.damage_reflected} damage.")
            target.health -= dealed_damage
            self.health -= target.damage_reflected
        else:
            print(f"{self.team.name} {type(self).__name__} attacks {target.team.name} {type(target).__name__} "
                  f"for {self.damage} damage.")
            target.health -= self.damage

        target.check_death()
        self.check_death()

    def check_death(self):
        if self.health <= 0:
            self.dead = True
            print(f"{self.team.name} {type(self).__name__} has died.")

class Goblin(Monster):
    def __init__(self, team, num_attacks=3):
        super().__init__(team, health=20, damage=7)
        self.num_attacks = num_attacks

    def attack(self, target):
        for _ in range(self.num_attacks):
            if target.dead or self.dead:
                break
            super().attack(target)

class Troll(Monster):
    def __init__(self, team, regen=5):
        super().__init__(team, health=100, damage=15)
        self.regen = regen

    def attack(self, target):
        super().attack(target)
        if self.health > 0:
            self.regenerate()

    def regenerate(self):
        print(f"{self.team.name} Troll regenerates {self.regen} health.")
        self.health += self.regen

class Orc(Monster):
    def __init__(self, team, damage_blocked=2, damage_reflected=2):
        super().__init__(team, health=40, damage=4)
        self.damage_blocked = damage_blocked
        self.damage_reflected = damage_reflected

    def attack(self, target):
        super().attack(target)

class Team(Enum):
    RED = 0
    BLUE = 1