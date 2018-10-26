/*
* Description: Misc. trigonometric formulas
*/

// given triangle side lengths a, b, c, returns angle between the sides with lengths a and b
ld angle_LOC(ld a, ld b, ld c)
{
    auto t = (a * a + b * b - c * c) / (2 * a * b);
    return acos(t);
}

// given triangle side lengths a and b and angle theta between them, returns the side length opposite theta
ld side_LOC(ld a, ld b, ld theta)
{
  return sqrt(a * a + b * b + 2 * a * b * cos(theta));
}

// given triangle side lengths a and b and angle theta between them, returns area of triangle
ld area_SAS(ld a, ld b, ld theta)
{
    return a * b * sin(theta) / 2.0;
}

/*
* law of sines: a / (sin alpha) = b / (sin beta) = 2 * circumradius 
* where a and b are side lengths, alpha and beta are angles opposite respectively
*/
