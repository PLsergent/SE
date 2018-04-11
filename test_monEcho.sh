#!/bin/bash

GOT="/tmp/`basename "$0"`-$$-got"
EXP="/tmp/`basename "$0"`-$$-exp"

test1() {
    echo >"$EXP"
    $CMD >"$GOT"
    compare_sortie "sortie avec 0 arguments"
}

test2() {
    echo hello >"$EXP"
    $CMD hello >"$GOT"
    compare_sortie "sortie avec 1 arguments"
}

test3() {
    echo hello world >"$EXP"
    $CMD hello world >"$GOT"
    compare_sortie "sortie avec 2 arguments"
}

test4() {
    echo hello wonderful world >"$EXP"
    $CMD hello wonderful world >"$GOT"
    compare_sortie "sortie avec 3 arguments"
}

test5() {
    echo a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u >"$EXP"
    $CMD a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u >"$GOT"
    compare_sortie "sortie avec 127 arguments"
}

test6() {
    $CMD >/dev/null
    verif_statut = 0 "statut avec 0 arguments"
}

test7() {
    $CMD hello >/dev/null
    verif_statut = 0 "statut avec 1 arguments"
}

test8() {
    $CMD hello world >/dev/null
    verif_statut = 0 "statut avec 2 arguments"
}

test9() {
    $CMD hello wonderful world >/dev/null
    verif_statut = 0 "statut avec 3 arguments"
}

test10() {
    $CMD a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u i o p a z e r t y u >/dev/null
    verif_statut = 0 "statut avec 127 arguments"
}

test11() {
    echo "hello  world" >"$EXP"
    $CMD "hello  world" >"$GOT"
    compare_sortie "sortie avec des guillemets"
}

test12() {
    echo " hello"     "world " >"$EXP"
    $CMD " hello"     "world " >"$GOT"
    compare_sortie "sortie avec des espaces avant et après"
}

test13() {
    $CMD hello world >/dev/full 2>"$GOT"
    verif_message "sortie sur erreur d'écriture"
}

test14() {
    $CMD hello wonderful world >/dev/full 2>/dev/null
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

CMD=./monEcho
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
