from monster import Goblin, Troll, Orc, Team

def main():
    # just an example scenario
    red = [Goblin(Team.RED), Troll(Team.RED), Goblin(Team.RED)]
    blue = [Goblin(Team.BLUE), Troll(Team.BLUE), Orc(Team.BLUE)]
    game_loop(red, blue)

def game_loop(red, blue):
    while red and blue:
        monster1 = red[0]
        monster2 = blue[0]

        while not monster1.dead and not monster2.dead:
            print_battle_intro(monster1, monster2)
            monster1.attack(monster2)
            print_barrier()

            # trash but works
            if monster1.dead:
                if red:
                    red.remove(monster1)
                    if red:
                        monster1 = red[0]
                    else:
                        break
                else:
                    break
            if monster2.dead:
                if blue:
                    blue.remove(monster2)
                    if blue:
                        monster2 = blue[0]
                    else:
                        break
                else:
                    break

            print_battle_intro(monster1, monster2)
            monster2.attack(monster1)
            print_barrier()

            if monster1.dead:
                if red:
                    red.remove(monster1)
                    if red:
                        monster1 = red[0]
                    else:
                        break
                else:
                    break
            if monster2.dead:
                if blue:
                    blue.remove(monster2)
                    if blue:
                        monster2 = blue[0]
                    else:
                        break
                else:
                    break

    if not red:
        print("Team BLUE wins!")
    elif not blue:
        print("Team RED wins!")

def print_battle_intro(monster1, monster2):
    print(f"[ RED | {type(monster1).__name__}({monster1.health}) ] vs [ {type(monster2).__name__}({monster2.health}) | BLUE ]")

def print_barrier():
    print("--------------------------------------------------------------------------")

if __name__ == "__main__":
    main()