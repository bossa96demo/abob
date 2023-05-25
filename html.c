#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/HTMLparser.h>
#include <string.h>

void print_node_info(xmlNode *node, int level) {

    printf("Tag: %d, name: %s\n", node->type, node->name);

    if (node->children != NULL) {
        print_node_info(node->children, level + 1);
    }

    if (node->next != NULL) {
        print_node_info(node->next, level);
    }
}

void parse_html(const char* html_content) {
    htmlDocPtr doc = htmlReadMemory(html_content, strlen(html_content), NULL, NULL, 0);

    if (doc == NULL) {
        fprintf(stderr, "Error: Failed to parse document\n");
        return;
    }

    xmlNodePtr root_element = xmlDocGetRootElement(doc);
    print_node_info(root_element, 0);

    xmlFreeDoc(doc);
}

int main(void) {
    const char* html_content = "<html><head><title>Test Document</title></head><body><p>Hello, world!</p></body></html>";
    parse_html(html_content);

    return 0;
}
