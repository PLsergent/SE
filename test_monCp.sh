#!/bin/bash

##
## Accepte un argument (optionnel) pour changer le nom de la commande à tester
##

GOT="/tmp/`basename "$0"`-$$-got"
EXP="/tmp/`basename "$0"`-$$-exp"

test1() {
    echo garbage >"$GOT"
    echo hello world >"$EXP"
    $CMD "$EXP" "$GOT"
    compare_sortie "contenue de la copie dans un fichier existant"
}

test2() {
    echo garbage >"$GOT"
    echo hello world >"$EXP"
    $CMD "$EXP" "$GOT"
    verif_statut = 0 "statut lors de la copie dans un fichier existant"
}

test3() {
    rm -f "$GOT"
    echo hello world >"$EXP"
    $CMD "$EXP" "$GOT"
    if [ -r "$GOT" -a -w "$GOT" -a \
         ! \( -u "$GOT" -o -g "$GOT" -o -k "$GOT" -o -x "$GOT" \) ]; then
        PASS=$(expr $PASS + 1)
    else
        echo "---- test$TEST: mode de la copie dans un nouveau fichier"
        echo -n "obtenu:  "; ls -l "$GOT" | cut -d " " -f 1
        echo    "attendu: -rw-**-**-"
    fi
    rm -f "$GOT" "$EXP"
}

test4() {
    rm -f "$GOT"
    echo hello world >"$EXP"
    $CMD "$EXP" "$GOT"
    compare_sortie "contenu de la copie dans un nouveau fichier"
}

test5() {
    rm -f "$GOT"
    echo hello world >"$EXP"
    $CMD "$EXP" "$GOT"
    verif_statut =  0 "statut de la copie dans un nouveau fichier"
}

test6() {
    echo "hello world" >"$EXP"
    chmod a-r "$EXP"
    $CMD "$EXP" /dev/null 2>"$GOT"
    verif_message "message sur erreur de lecture"
}

test7() {
    echo "hello world" >"$EXP"
    chmod a-r "$EXP"
    $CMD "$EXP" /dev/null 2>"$GOT"
    verif_statut !=  0 "statut sur erreur de lecture"
}

test8() {
    echo "hello world" >"$EXP"
    chmod a-r "$EXP"
    echo "hello world" >"$GOT"
    $CMD "$EXP" "$GOT" 2>/dev/null
    echo "hello world" >"$EXP"
    chmod a+r "$EXP"
    compare_sortie "fichier destination non changé sur erreur de lecture"
}

test9() {
    rm -f "$EXP"
    $CMD "$EXP" /dev/null 2>"$GOT"
    verif_message "message si fichier source inexistant"
}

test10() {
    rm -f "$EXP"
    $CMD "$EXP" /dev/null 2>"$GOT"
    verif_statut !=  0 "statut si fichier source inexistant"
}

test11() {
    echo "hello world" >"$GOT"
    rm -f "$EXP"
    $CMD "$EXP" "$GOT" 2>/dev/null
    echo "hello world" >"$EXP"
    compare_sortie "fichier destination non changé si fichier source inexistant"
}

test12() {
    echo "hello world" >"$EXP"
    $CMD "$EXP" /dev/full 2>"$GOT"
    verif_message "message sur erreur d'écriture"
}

test13() {
    echo "hello world" >"$EXP"
    $CMD "$EXP" /dev/full 2>"$GOT"
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

CMD=./monCp
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
