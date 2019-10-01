# startingover -- shmupwarz-cpp

    A sort of a port of a port of a sort.
    A port is a port of a sort of a sort.
    And of course the name of the port is...
    The famous GL Ewe.

Hmm - instead of talking horses, we got colorful sheep?

### does not work on Raspbian Buster 

    too bad, but glew.h is not compatible with gl.h - due to redefinition using ptrdiff_t.
    So, no sheep.

### "It'll be just like starting over" -- John Lennon
 
    use doran (cmake) to build desktop version
    use ctrl-b to build emscripten version

goals & vision - put the lime in the coconut

    colocation of data as in better-mousetrap - array of struct
    entitas style extension to make c++ static typeing more fluid
    artemis architecture for the engine using typescript
    mix of opengl & sdl2 similar to monogame
    run on desktop and emscripten

    replace vala and zerog with c++17. As much as I like vala, valagame must die. 
    I learned about impelementing a monogame style engine using c/cpp.

    
### coding convention

    Follows the MSDN convention - all public clases and members are PascalCase, parameters and locals are camelCase, member fields may be private mPascalCase

    the close coupling beteen GameSystems and Shmupwarz causes cyclic dependencies, which in turn require separation of *.ccp and *.h... I need to implement ArtemisCCP to resolve this typr of thing


### fix yer timestep:
```
double t = 0.0;
double dt = 0.01;

double currentTime = hires_time_in_seconds();
double accumulator = 0.0;

State previous;
State current;

while ( !quit )
{
    double newTime = time();
    double frameTime = newTime - currentTime;
    if ( frameTime > 0.25 )
        frameTime = 0.25;
    currentTime = newTime;

    accumulator += frameTime;

    while ( accumulator >= dt )
    {
        previousState = currentState;
        integrate( currentState, t, dt );
        t += dt;
        accumulator -= dt;
    }

    const double alpha = accumulator / dt;

    State state = currentState * alpha + 
        previousState * ( 1.0 - alpha );

    render( state );
}
```