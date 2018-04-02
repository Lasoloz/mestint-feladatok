% From StackOverflow
% https://stackoverflow.com/questions/23176840/easily-replicate-an-element-in-prolog
repl(X, N, L) :-
    length(L, N),
    maplist(=(X), L).


% Problem:

% zzz_sss
% Zöld és sárga békák problémája. Zöldek csak balra, sárágk csak jobbra
% ugorhatnak

lep(([z|Tb],Tj), (Tb,[z|Tj]), z1).
lep((Tb,[s|Tj]), ([s|Tb],Tj), s1).
lep((Tb,[z,s|Tj]), ([z,s|Tb],Tj), s2).
lep(([s,z|Tb],Tj), (Tb,[s,z|Tj]), z2).


ut((Lb,Lj),(Lb, Lj),[]).
ut((Lb,Lj), (LbE, LjE), [Step|TStep]):-
    lep((Lb, Lj), (LbT, LjT), Step),
    ut((LbT, LjT), (LbE, LjE), TStep).


beka(Db, Result):-
    repl(z, Db, L),
    repl(s, Db, R),
    ut((L,R), (R,L), Result).
