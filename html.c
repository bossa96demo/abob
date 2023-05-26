#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/HTMLparser.h>
#include <libxml/tree.h>
#include <string.h>

void print_node_info(xmlNode *node, int level, void (*callback)(char *)) {

    callback((char*)node->name);
    char *content = (char *)xmlNodeGetContent(node);
    //printf("%s", content);


    if (node->children != NULL) {
        print_node_info(node->children, level + 1, callback);
    }

    if (node->next != NULL) {
        print_node_info(node->next, level, callback);
    }
}

void parse(char* html_content, void (*callback)(char *)) {
    htmlDocPtr doc = htmlReadMemory(html_content, strlen(html_content), NULL, NULL, 0);

    if (doc == NULL) {
        fprintf(stderr, "Error: Failed to parse document\n");
        return;
    }

    xmlNodePtr root_element = xmlDocGetRootElement(doc);
    print_node_info(root_element, 0, callback);

    xmlFreeDoc(doc);
}
