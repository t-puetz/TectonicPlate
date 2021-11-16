# TectonicPlate code styleguide

## Abbreviation of identifiers

Identifiers are heavily abbreviated to avoid long names as good as possible

*  Vk        = Vulkan
*  Tp        = TectonicPlate
*  advances  = adv
*  arr       = array
*  app       = application
*  cmp       = compare
*  cntr      = counter
*  creat     = create
*  dev       = device
*  devs      = devices
*  dptr      = pointer pointer (double pointer)
*  dsld      = disabled
*  enbld     = enabled
*  extn      = extension
*  extns     = extensions
*  fam       = family
*  feat      = feature
*  feats     = features
*  frag      = fragment
*  frags     = fragments
*  gpu       = phys_dev
*  goi       = gpu of interest (GPU user/engine chose to use)
*  idx       = index
*  inf       = info
*  inst      = instance
*  ivald     = invalid
*  lay       = layer
*  lays      = layers
*  len       = length
*  maj       = major (version)
*  min       = minor (version)
*  mem       = memory
*  mlsamp    = multisampling
*  mod       = mode
*  mods      = modes
*  modl      = module
*  modls     = modules
*  n         = and / placeholder for numeric value
*  nm        = name
*  nms       = names
*  num       = number
*  dev       = device
*  logic_dev = logical device aka logical abstraction of GPU
*  p         = pointer
*  pat       = patch (version)
*  phys      = physical
*  pipl      = pipeline
*  prelim    = preliminary
*  prep      = prepare
*  preptn    = preparation
*  prop      = property
*  props     = properties
*  plmsone   = preliminary work for stage 1 (right before init of stage, so like stage 0.5 or so)
*  plmstwo   = preliminary work for stage 2 (right before init of stage, so like stage 1.5 or so) 
               and so on. You will figure out plmsthree, plsmfour, plsmfive yourself ;)
*  res       = result
*  scss      = scissor
*  sone      = stage one
*  stg       = stage
*  str       = string
*  stwo      = stage two
*  strct     = struct
*  tptr      = triple pointer
*  sur       = surface
*  swc       = swapchain
*  phys_dev  = physical device aka GPU
*  q         = queue
*  qptr      = quadruple pointer
*  val       = value
*  vals      = values
*  vald      = valid
*  valdtr    = validator
*  vcs       = verteces
*  vx        = vertex
*  w         = with


Exceptions. The second level tp wrapper functions do not use creat but the full word create in their name.
This way the *create* in TectonicPlate functions is distinguishable from the *create_inf* that usually describes Vk structs that habe *CreateInfo" in their name.

All in all this code can still lead to long lines. I will set the **line limit to 120** columns for now.
We live in the year 2020. Live with it. Would be great to know how to write my own formatter, though ^^.

***phys_dev* and *gpu* are synonymes.**

## Style of identifiers

* **Snake case** (I will call what is inbetween underscores syllables)
* An exception are the vulkan identifiers which are upper camel case. Doh!
* **variable and function names are completely lower case**
* For **structs and enums each syllable starts with an uppercase letter are continued lower case**
* Acronyms from the real world that are usually all uppercase stay all uppercase enums and structs. In variables and function they are written all lowercase.
* **Hungarian notation using for arr, str, strct, ptr is allowed**, but should be avoided if extremely obvious
* **Hungarian notation is not allowed for primitive types**: For number types use something like num, cntr or such.


* #### Examples:
    * 1) ```
             Tp_GPUs* ptr_gpus = tp_create_vk_phys_devs(ptr_tp_vk_inst_fam->ptr_vk_inst);
    * 2) ```
             char** inst_val_lay_nm_arr = malloc(sizeof(char*));

## Style of tokens
* Of course language built-in keywords cannot be changed, but this section is to describe "keywords" you define yourself such as when you typedef structs or enums.
* Structs and Enum type names are snake case where each syllable starts with an upper case letter and continues lowercase. This avoids confusion when the chosen identifier name for a declared struct is very similar to the struct typename itself.

## Style of indentation

* One level of **indentation** is represented by **4 spaces**

## Style of comments

* One line comments are written in */\* \*/* with a space after the opening and before the closing token
* Everything more than two lines **must** be written with the multiline comment tokens */\*\* \*\*/*. Enclosing spaces rule is the same as above. Each new line in the multiline comment starts with a *\** and two spaces so that the actual start of each line within the multiline comment aligns.

## Style of curly braces

* Major, first level functions in headers and c files are written in C-style where the opening curly brace and the closing curly brace are solely on their own line. The only exception here is that the closing curly brace can also have a semicolon right next to it. The opening curly brace follws right after the function prototype and the closing curly brace right after the last line of code.
* Within the functions *if*, *else*, *for*, *while* and such use the Java-style where the opening curly brace is on the same line as the line of code introducing the keyword. The closing curly brace has its own line. It should be the only character on that line except when followed by a semicolon. Again the code within those blocks has no empty line break in the beginning nor at the end.
* If and else that are only followed by are single statement **must not** be enclosed in curly braces. If they are short let them stay on the same line, if they are long move them onto a new line and indent them.
* If a semicolon has to follow a closing curly brace it **must be** placed directly after it. For typedefs, e.g. for structs, where the struct name follows with a semicolon, the struct name follows seperated by a space from the closing curly brace.

* #### Examples:
  1) ``` 
        int main(int argc, char* argv[]) 
        {
            char* app_nm = "TectonicPlate Triangle Example";
        }

## Style of parentheses

* Parantheses that follow a keyword or identifier are not seperated with a space, but the opening parentheses directly follows the identifier or keyword.
* Code inside the parentheses is not seperated with a space from the opening and the closing parentheses.
* See example in above section

## Style of square brackets
* Same as the style rules as for parentheses

## Style of linebreaks
* Somewhat the use of line breaks has been already defined by the rules stated above. This section is for all the missing cases.
* A return **always** follows after a empty linebreak
* When blocks of are directly nested, so a *if* would directly *while* for example I can only give advice.
* In my humble opinion two to three nested keywords should not be seperated by linebreaks. If blocks from keywords that follow directly onto each other, the occuring nesting still looks quite elegant if the blocks inside the keyword only have few lines of code in them. You should use linebreaks to seperate the keywords if you think it is hard for the eye to easily spot that a nesting of blocks is going on. So if you have many layers of nesting that each have a lot of code in them, you should definitely seperate them from the next block on the same level and/or from superior or inferior block with a linebreak before and a linebreak after the block.
* Again inside blocks there are no empty line breaks after the opening curly brace or before the closing curly brace.
* Your code should avoid excessive use of linebreaks. However, line breaks should be used to seperate sections of code from each other logically. Declaration is seperated from initialization is seperated from preliminary work is seperated from final work and so on. Also as stated above: If linebreaks help you break up a lot of code to make it easier for the eye to grasp what's happening then you are encouraged to use same.

## Style of operators
* Operator are **always** seperated from the rest of the code like this: \<space\>\<operator\>\<space\>
* Incrementor and decrementor, ++ and --, are one exception 
* Derefence and reference operator, * and &, the other. I hope I have accounted for all exceptions.

* #### Examples:
    1) ```
        VkApplicationInfo* ptr_vk_app_inf = tp_create_vk_app_inf(app_nm, maj, min, pat);
    2) ```
        for(uint8_t i = 0; i < arr_len; i++)

## Style of pointers
* Ok this is probably where experienced programmers will hate me. And I am at most an amateur. But IMHO the guy that thought the asteriks *\** would be a good choice for declaring pointers and also for dereferencing them should be at least slapped on his fingers. It causes so many ugly and confusing ambiguities (pointer declaration plus derefencing plus multiplying quickly derail into a shitshow). And the *&* operator is also not a good choice. Not as bad as *\**, but nevertheless shitty.

And now comes the part where I go against decade old *de-facto* conventions:

I declare a pointer like this:

    char* str = "";
        
**NOT LIKE THIS**

    char *str = "";

**AND MOST CERTAINLY NOT LIKE THIS**

    char * str = "";

Maybe I am stupid, but for my brain this is so much easier to read. I declare something with the type of char pointer (out of *char\** my brain simply makes the words "char pointer") with the identifier named *str*.
I do not declare something that when dereferenced is a char and the fact that it is a pointer by putting the \* to the identifier. No way my brain can process this in one read just by spotting the tokens.
And I most f'ing certainly don't want to multiply a char with an identifier named *str*.

* Now that that is out of the way: Next rule:
The result of malloc nowadays is a *void\**. A long time ago even before ANSI C it was *char\** and that's why it was casted. The casting is not neccessary anymore and makes the code hard to read.

* Malloc is used like this
    
    ```
        Tp_Init_Vk* tp_vk_init_data = malloc(sizeof(Tp_Init_Vk));
    ```

    * there is **no casting** of the result
    * *sizeof*  (Yes, I know it's a macro not a function) uses parenthesis and inside 
      you put the type you want to malloc
    * You **don't** dereference that type by using \*\<identifier\> \*\<pointer_of_type\>
    * And you **never ever** do this:
        ```
            Tp_Init_Vk* tp_vk_init_data = malloc(sizeof * Tp_Init_Vk);

    * and **if you do this I will haunt you until the end of time**
        ```
            Tp_Init_Vk* tp_vk_init_data = malloc(length * sizeof * Tp_Init_Vk);
    
    * and if you have no Fs to give about my wrath and you want to destroy the universe here ya go:
        ```
           Tp_Init_Vk * tp_vk_init_data = (Tp_Init_Vk *)malloc(length * sizeof * Tp_Init_Vk);
