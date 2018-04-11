#!/bin/bash

GOT="/tmp/`basename "$0"`-$$-got"
EXP="/tmp/`basename "$0"`-$$-exp"

test1() {
    echo "Hello world">"$EXP"
    $CMD >"$GOT"
    compare_sortie "sortie du programme"
}

test2() {
    echo -n >"$EXP"
    $CMD 2>"$GOT" >/dev/null
    compare_sortie "sortie (stderr) du programme"
}

test3() {
    $CMD >/dev/null
    verif_statut = 0 "statut du programme"
}

test4() {
    $CMD >/dev/full 2>"$GOT"
    verif_message "sortie sur erreur d'écriture"
}

test5() {
    $CMD >/dev/full 2>/dev/null
    verif_statut != 0 "statut sur erreur d'écriture"
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

CMD=./hello
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
