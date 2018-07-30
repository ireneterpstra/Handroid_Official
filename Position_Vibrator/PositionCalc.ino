// β -> angle btwn x & y axis
// α -> angle btwn y & z axis
//  x = rcosβsinα  
//  y = rcosβcosα
//  z = rsinβ

void calcElbowPos(int r){
  int a = -BX1 + 90;
  int b = BZ1;
  x1 = r * cos(b * M_PI / 180) * sin(a * M_PI / 180); 
  y1 = r * cos(b * M_PI / 180) * cos(a * M_PI / 180); 
  z1 = r * sin(b * M_PI / 180); 
}

void calcHandPos(int r){
  int a = -BX + 90;
  int b = BZ;
  x2 = x1 + r * cos(b * M_PI / 180) * sin(a * M_PI / 180); 
  y2 = y1 + r * cos(b * M_PI / 180) * cos(a * M_PI / 180); 
  z2 = z1 + r * sin(b * M_PI / 180); 
}

