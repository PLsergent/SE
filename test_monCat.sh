#!/bin/bash

GOT="/tmp/`basename "$0"`-$$-got"
EXP="/tmp/`basename "$0"`-$$-exp"

test1() {
    echo hello world >"$EXP"
    cat "$EXP" | $CMD >"$GOT"
    compare_sortie "sortie du programme"
}

test2() {
    echo -n >"$EXP"
    cat "$EXP" | $CMD >"$GOT"
    echo > "$EXP" # because $CMD will add a newline
    compare_sortie "sortie du programme (entrée vide)"
}


test3() {
    echo "hello" >"$EXP"
    echo -n "hello" | $CMD >"$GOT"
    compare_sortie "sortie du programme (ligne incomplète)"
}

test4() {
    echo hello >"$EXP"
    (echo hello; echo world) | $CMD >"$GOT"
    compare_sortie "sortie du programme (entrée sur plusieurs lignes)"
}

test5() {
    echo -n >"$EXP"
    echo hello world | $CMD 2>"$GOT" >/dev/null
    compare_sortie "sortie (stderr) du programme"
}

test6() {
    echo hello world | $CMD >/dev/null
    verif_statut = 0 "statut du programme"
}


test7() {
    echo -n >"$EXP"
    cat "$EXP" | $CMD >/dev/null
    verif_statut = 0 "statut du programme (entrée vide)"
}

test8() {
    (echo hello; echo wonderful; echo world) | $CMD >/dev/null
    verif_statut = 0 "statut du programme (entrée sur plusieurs lignes)"
}

test9() {
    echo hello world | $CMD >/dev/full 2>"$GOT"
    verif_message "sortie sur erreur d'écriture"
}

test10() {
    echo hello world | $CMD >/dev/full 2>/dev/null
    verif_statut != 0 "statut sur erreur d'écriture"
}

test11() {
    echo -n >"$EXP"
    cat "$EXP" | $CMD hello world >"$GOT"
    echo > "$EXP" # because $CMD will add a newline
    if diff "$EXP" "$GOT" -q >/dev/null; then
        PASS=$(expr $PASS + 1)
    else
        echo "---- test$TEST: sortie avec des arguments"
        echo "les arguments doivent être ignorés"
        echo "les données affichées doivent provenir de l'entrée standard"
    fi
}

test12() {
    echo helloworld >"$EXP"
    (echo -n hello; sleep 1; echo world) | $CMD >"$GOT"
    compare_sortie "sortie en deux temps"
}

test13() {
    (for i in {1..100000}; do echo -n x; done; echo) >"$EXP"
    cat "$EXP" | $CMD >"$GOT"

    if diff "$EXP" "$GOT" -q >/dev/null; then
        PASS=$(expr $PASS + 1)
    else
        echo "---- test$TEST: $1"
        echo -n "obtenu:  (taille) "; wc -c "$GOT" | cut -f1 -d" "
        echo -n "attendu: (taille) "; wc -c "$EXP" | cut -f1 -d" "
    fi
    rm -f "$GOT" "$EXP"
}


######## fonctions utilitaires ########

PASS=0
TEST=0

compare_sortie() {
    if diff "$EXP" "$GOT" -q >/dev/null; then
        PASS=$(expr $PASS + 1)
    else
        echo "---- test$TEST: $1"
        echo -n "obtenu:  <"; cat "$GOT"; echo ">"
        echo -n "attendu: <"; cat "$EXP"; echo ">"
    fi
    rm -f "$GOT" "$EXP"
}

verif_statut() {
    statut=$?
    if [ "$1" = "=" ]; then op="-eq"; else op="-ne"; fi
    if [ $statut $op $2 ]; then
        PASS=$(expr $PASS + 1)

    else
        echo "---- test$TEST: $3"
        echo "obtenu:  $statut"
        echo "attendu: $1 $2"
    fi
}

verif_message() {
    if [ "$(cat "$GOT")" != "" ]; then
        PASS=$(expr $PASS + 1)
    else
        echo "---- test$TEST: $1"
        echo "un message devrait être affiché sur l'erreur standard"
    fi
}


######## programme principal ########
# exécute tous les tests dans l'ordre

CMD=./monCat
if [ ! -x "$CMD" ]; then
    echo "commande $CMD introuvable"
    exit -1
fi

while true; do
    TEST=$(expr $TEST + 1)
    type -t test$TEST >/dev/null || break
    test$TEST
done
TEST=$(expr $TEST - 1)
echo ">>>> $PASS/$TEST tests passés"
rm -f "$GOT" "$EXP"
test "$PASS" -eq "$TEST"
exit $?
