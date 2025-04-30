# le-dernier-serment/The Last Oath
Adventure game for amstrad cpc :

English version : https://narkhos.itch.io/the-last-oath

Version française : https://narkhos.itch.io/le-dernier-serment

## Note to translators

Here is a little roadmap to translate Le Dernier Serment in another language:

- database_xx.c contains all the objects and locations of the game with their names and description.
- language_xx.h contains all the texts for story and menus.
- parser/parser.c contains the list of verbs (and synonyms), and a list of words to ignore in the prompt
-  _c_SDCC3.bat is the compilation script. It needs to be modified to accept the new language parameter
- anywhere in the code where you found #if LANGUAGE == 1 need to be adapted for each language.
- The title screen is an image, we can keep the English title for every language (or we will need to draw the title for each lanaguage)
- DISC_XX.BAS is the launcher in basic, we can duplicate the english version. The only text in their is to warn people who don't have 128kb ram (it can be kept in english or translated. The text is 'The Last Oath needs 128kb of RAM to run'
