#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decl.h"
#include "expr.h"
#include "stmt.h"
#include "type.h"


/*
struct decl {
	char *name;
	struct type *type;
	struct expr *value;
	struct stmt *code;
	struct symbol *symbol;
	struct decl *next;
};
*/

void decl_translate(struct decl *d, char *cpp_translations) {
    if (d == NULL || cpp_translations == NULL)
        return;

    while (d != NULL) {
        char temp[4096] = "";

        type_translate(d->type, d->name, temp);
        strcat(cpp_translations, temp);

        if (d->type != NULL && d->type->kind == TYPE_FUNCTION) {
            strcat(cpp_translations, "(");

            if (d->type->params != NULL) {
                temp[0] = '\0';
                param_list_translate(d->type->params, temp);
                strcat(cpp_translations, temp);
            }

            strcat(cpp_translations, ")");

            if (d->code != NULL) {
                temp[0] = '\0';
                stmt_translate(d->code, temp);
                strcat(cpp_translations, temp);
            } else {
                strcat(cpp_translations, ";");
            }
        } else {
            if (d->value != NULL) {
                strcat(cpp_translations, " = ");
                temp[0] = '\0';
                expr_translate(d->value, temp);
                strcat(cpp_translations, temp);
            }

            strcat(cpp_translations, ";");
        }

        if (d->next != NULL)
            strcat(cpp_translations, "\n");

        d = d->next;
    }
}
