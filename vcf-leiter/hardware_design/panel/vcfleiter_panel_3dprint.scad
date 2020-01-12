width = 30;
thickness = 2;
jack_radius = 6.1 / 2;
pot_radius = 7.1 / 2;

x_offset = (128.5 - 100) / 2;

jacks = [[7.5, 8], [22.5, 8], [7.5, 26], [7.5, 44]];
pots = [[22.5, 26], [22.5, 62], [7.5, 62], [15, 84]];

difference() {
    cube(size = [128.5, width, thickness]);

    for (jack = jacks)
        translate([jack[1] + x_offset, jack[0], -thickness / 2]) linear_extrude(height = thickness * 2) circle(r = jack_radius, $fn = 100);
    
    for (pot = pots)
        translate([pot[1] + x_offset, pot[0], -thickness / 2]) linear_extrude(height = thickness * 2) circle(r = pot_radius, $fn = 100);
    
    // top hole
    translate([125.5, 7.5, -thickness / 2]) linear_extrude(height = thickness * 2) circle(r = 3.2 / 2, $fn = 10);
    //translate([125.5, 7.5 + 3 * 5.8, 0]) circle(r = 3.2 / 2, $fn = 10);
    
    //bottom hole
    translate([3, 7.5, -thickness / 2]) linear_extrude(height = thickness * 2) circle(r = 3.2 / 2, $fn = 100);
}