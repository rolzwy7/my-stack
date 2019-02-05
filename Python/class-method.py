# class method example

class Mob():

    _GLOBAL_DEBUFF = False

    def __init__(self, name, health, attack, defense):

        self.name = name
        self.health = health
        self.attack = attack
        self.defense = defense
        self.dead = False

    def damage(self, hit_points):
        print("damage called with {} hit points".format(hit_points))
        hit_points = hit_points * 1.5 if self._GLOBAL_DEBUFF else hit_points

        self.health -= hit_points
        print("{} hit for {}".format(self.name, hit_points))

        if self.health <= 0:
            print("{} is dead".format(self.name))
            self.dead = True

    def print_info(self):
        print(
        '''
        Name    : {name}
        Health  : {health}
        Attack  : {attack}
        Defense : {defense}
        '''.format(**self.__dict__)
        )

    @classmethod
    def set_global_debuff(cls, state):
        cls._GLOBAL_DEBUFF = state

black_orc = Mob("Black Orc", 500., 50., 25.)

print("Before first hit")
black_orc.print_info()

black_orc.damage(15)

print("After first hit")
black_orc.print_info()

Mob.set_global_debuff(True)
black_orc.damage(50)

print("After second hit with debuff")
black_orc.print_info()
