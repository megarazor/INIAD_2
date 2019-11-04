while True:
  num_turtles= int(input('Enter the number of turtles: '))
  total_legs= int(input('Enter the number of legs in total: '))
  num_cranes= (total_legs - num_turtles*4) // 2
  print('The number of cranes:', num_cranes)
